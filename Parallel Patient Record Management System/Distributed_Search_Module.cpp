#include "Distributed_Search_Module.h"
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <mpi.h>

using namespace std;

unordered_map<string, string> indexedRecords;

Distributed_Search_Module::Distributed_Search_Module() {}

Distributed_Search_Module::~Distributed_Search_Module() {}

void readPatientRecordsFromFile(const string& filename, vector<string>& patientRecords);
void indexPatientRecords(const vector<string>& patientRecords);

void Distributed_Search_Module::execute() {
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int searchIndex = -1;
    if (world_rank == 0) {
        // Prompt the user to enter the search index
        cout << "Enter the search index: ";
        cin >> searchIndex;
    }

    // Broadcast the search index to all processes
    MPI_Bcast(&searchIndex, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Read patient records from files
    vector<string> patientRecords;
    readPatientRecordsFromFile("Patient_Records.txt", patientRecords);
    readPatientRecordsFromFile("Additional_Patient_Records.txt", patientRecords);
    readPatientRecordsFromFile("Extra_Patient_Records.txt", patientRecords);

    // Distribute patient records among processes
    distributePatientRecords(patientRecords, world_rank);

    // Index and search patient records
    indexAndSearchPatientRecords(world_rank, searchIndex, patientRecords);
}

void Distributed_Search_Module::readPatientRecordsFromFile(const string& filename, vector<string>& patientRecords) {
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

void Distributed_Search_Module::distributePatientRecords(const vector<string>& patientRecords, int world_rank) {
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int numRecordsPerProcess = patientRecords.size() / world_size;
    int remainder = patientRecords.size() % world_size;

    vector<string> localRecords;
    if (world_rank == 0) {
        // Scatter patient records to all processes
        for (int i = 0; i < world_size; ++i) {
            int start_index = i * numRecordsPerProcess;
            int end_index = start_index + numRecordsPerProcess;
            if (i == world_size - 1) {
                end_index += remainder; // Last process handles extra records
            }
            MPI_Scatter(patientRecords.data() + start_index, end_index - start_index, MPI_CHAR, localRecords.data(), end_index - start_index, MPI_CHAR, 0, MPI_COMM_WORLD);
        }
    } else {
        localRecords.resize(numRecordsPerProcess);
        MPI_Scatter(nullptr, 0, MPI_CHAR, localRecords.data(), numRecordsPerProcess, MPI_CHAR, 0, MPI_COMM_WORLD);
    }
}

void Distributed_Search_Module::indexAndSearchPatientRecords(int world_rank, int searchIndex, const vector<string>& patientRecords) {
    // Index patient records based on keywords
    indexPatientRecords(patientRecords);

    // Perform distributed search
    searchPatientRecords(world_rank, searchIndex);
}

void Distributed_Search_Module::indexPatientRecords(const vector<string>& patientRecords) {
    for (const auto& record : patientRecords) {
        stringstream ss(record);
        string field, keyword;
        while (getline(ss, field, ',')) {
            if (field.find("Allergy") != string::npos || field.find("Flu") != string::npos || field.find("Diabetes") != string::npos) {
                indexedRecords[field] = record;
                break;
            }
        }
    }

    cout << "Indexing completed successfully." << endl;
}

void Distributed_Search_Module::searchPatientRecords(int world_rank, int searchIndex) {
    cout << "Process " << world_rank << " searching records for index " << searchIndex << "..." << endl;
    for (const auto& pair : indexedRecords) {
        if (pair.first.find(to_string(searchIndex)) != string::npos) {
            cout << "Matching record found: " << pair.second << endl;
        }
    }
}
