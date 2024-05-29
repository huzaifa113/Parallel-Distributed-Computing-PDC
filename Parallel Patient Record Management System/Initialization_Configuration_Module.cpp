#include "Initialization_Configuration_Module.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <mpi.h>

using namespace std;

Initialization_Configuration_Module::Initialization_Configuration_Module() {}

Initialization_Configuration_Module::~Initialization_Configuration_Module() {}

void Initialization_Configuration_Module::execute() {
    initializeMPI();
    parsePatientConfiguration();
    establishMPICommunicators();
}

void Initialization_Configuration_Module::initializeMPI() {
    MPI_Init(NULL, NULL);
}

void Initialization_Configuration_Module::parsePatientConfiguration() {
    vector<string> patientRecords;
    vector<string> additionalPatientRecords;
    vector<string> extraPatientRecords;

    // Read Patient_Records file
    ifstream patientFile("Patient_Records.txt");
    if (!patientFile) {
        cerr << "Error: Unable to open Patient_Records file.\n";
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    string line;
    while (getline(patientFile, line)) {
        patientRecords.push_back(line);
    }
    patientFile.close();

    // Read Additional_Patient_Records file
    ifstream additionalFile("Additional_Patient_Records.txt");
    if (!additionalFile) {
        cerr << "Error: Unable to open Additional_Patient_Records file.\n";
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    while (getline(additionalFile, line)) {
        additionalPatientRecords.push_back(line);
    }
    additionalFile.close();

    // Read Extra_Patient_Records file
    ifstream extraFile("Extra_Patient_Records.txt");
    if (!extraFile) {
        cerr << "Error: Unable to open Extra_Patient_Records file.\n";
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    while (getline(extraFile, line)) {
        extraPatientRecords.push_back(line);
    }
    extraFile.close();

    // Now you have vectors containing the records from each file
    // You can process these vectors further as needed
}

void Initialization_Configuration_Module::establishMPICommunicators() {
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Determine color value based on node properties or rank
    int color = world_rank % 2; // For example, alternate colors based on rank

    // Split MPI_COMM_WORLD into subgroups based on color
    MPI_Comm subgroup_comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &subgroup_comm);

}

