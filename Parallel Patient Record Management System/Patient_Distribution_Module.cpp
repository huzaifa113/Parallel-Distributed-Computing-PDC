#include "Patient_Distribution_Module.h"
#include <fstream>
#include <iostream>
#include <mpi.h>
#include <string>
#include <vector>

using namespace std;

Patient_Distribution_Module::Patient_Distribution_Module() {}

Patient_Distribution_Module::~Patient_Distribution_Module() {}

void readPatientRecordsFromFile(const string& filename, vector<string>& patientRecords);

void Patient_Distribution_Module::execute() {
    vector<string> patientRecords;

    // Read patient records from files
    readPatientRecordsFromFile("Patient_Records.txt", patientRecords);
    readPatientRecordsFromFile("Additional_Patient_Records.txt", patientRecords);
    readPatientRecordsFromFile("Extra_Patient_Records.txt", patientRecords);

    distributePatientRecords(patientRecords);
}

void readPatientRecordsFromFile(const string& filename, vector<string>& patientRecords) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        patientRecords.push_back(line);
    }
    file.close();
}

void Patient_Distribution_Module::distributePatientRecords(const vector<string>& patientRecords) {
    // Initialize MPI
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Calculate chunk size for each process
    int chunk_size = patientRecords.size() / world_size;
    int remainder = patientRecords.size() % world_size;

    // Allocate memory for local patient records
    vector<string> localRecords(chunk_size + (world_rank == world_size - 1 ? remainder : 0));

    // Distribute patient records using MPI_Scatter
    MPI_Scatter(patientRecords.data(), chunk_size, MPI_CHAR, localRecords.data(), chunk_size, MPI_CHAR, 0, MPI_COMM_WORLD);

    // Print locally distributed records (for demonstration)
    cout << "Process " << world_rank << " received " << localRecords.size() << " records:" << endl;
    for (const auto& record : localRecords) {
        cout << record << endl;
    }
    cout << endl;

    // Finalize MPI
    MPI_Finalize();
}
