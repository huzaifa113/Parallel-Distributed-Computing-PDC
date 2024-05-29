#include "Implementing_Operations_Module.h"
#include "Logging_Module.h"
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <mpi.h>
#include <fstream>
using namespace std;

// Placeholder data structure to store patient records
unordered_map<string, string> patientDatabase;

Implementing_Operations_Module::Implementing_Operations_Module() {}

Implementing_Operations_Module::~Implementing_Operations_Module() {}

void readPatientRecordsFromFile(const string& filename, vector<string>& patientRecords);

Logging_Module loggingModule;

void Implementing_Operations_Module::execute() {
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

 // Read patient records from files
    vector<string> patientRecords;
    readPatientRecordsFromFile("Patient_Records.txt", patientRecords);
    readPatientRecordsFromFile("Additional_Patient_Records.txt", patientRecords);
    readPatientRecordsFromFile("Extra_Patient_Records.txt", patientRecords);

    int choice;
    string record;
    cout<<"1) Add Patient record: " << endl;
    cout<<"2) Update Patient record: " << endl;
    cout<<"3) Delete Patient record: " << endl;
    cout<<"Enter Your Choice: " << endl;
    cin>>choice;

    switch (choice) {
        case 1:
            cout << "Enter patient record (ID, Age, Gender, Blood Type, Date of Diagnosis, Diagnosis): ";
            getline(cin, record);
            addPatientRecord(record);
            break;
        case 2:
            cout << "Enter updated patient record (ID, Age, Gender, Blood Type, Date of Diagnosis, Diagnosis): ";
            getline(cin, record);
            updatePatientRecord(record);
            break;
        case 3:
            cout << "Enter patient record ID to delete: ";
            getline(cin, record);
            deletePatientRecord(record);
            break;
        default:
            cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
            break;
    }
}

void Implementing_Operations_Module::addPatientRecord(const string& record) {
    // Split record into fields
    stringstream ss(record);
    vector<string> fields;
    string field;
    while (getline(ss, field, ',')) {
        fields.push_back(field);
    }

    // Check if record with the same ID already exists
    string recordID = fields[0];
    if (patientDatabase.find(recordID) != patientDatabase.end()) {
        cout << "Error: Record with ID " << recordID << " already exists." << endl;
        return;
    }

    // Store record in the database
    patientDatabase[recordID] = record;
    cout << "Added patient record: " << record << endl;

    string logMessage = "Added patient record with ID " + recordID;
    loggingModule.logOperation(logMessage);
}

void Implementing_Operations_Module::updatePatientRecord(const string& record) {
    // Split record into fields
    stringstream ss(record);
    vector<string> fields;
    string field;
    while (getline(ss, field, ',')) {
        fields.push_back(field);
    }

    // Check if record with the same ID exists
    string recordID = fields[0];
    if (patientDatabase.find(recordID) == patientDatabase.end()) {
        cout << "Error: Record with ID " << recordID << " does not exist." << endl;
        return;
    }

    // Update record in the database
    patientDatabase[recordID] = record;
    cout << "Updated patient record: " << record << endl;

    string logMessage = "updated patient record with ID " + recordID;
    loggingModule.logOperation(logMessage);
}

void Implementing_Operations_Module::deletePatientRecord(const string& recordID) {
    // Check if record with the given ID exists
    if (patientDatabase.find(recordID) == patientDatabase.end()) {
        cout << "Error: Record with ID " << recordID << " does not exist." << endl;
        return;
    }

    // Delete record from the database
    patientDatabase.erase(recordID);
    cout << "Deleted patient record with ID: " << recordID << endl;

    string logMessage = "Deleted patient record with ID " + recordID;
    loggingModule.logOperation(logMessage);
}

void Implementing_Operations_Module::readPatientRecords() {
    // Read all patient records from the database
    cout << "Patient Records:" << endl;
    for (const auto& pair : patientDatabase) {
        cout << pair.second << endl;
    }
}


void Implementing_Operations_Module::readPatientRecordsFromFile(const string& filename, vector<string>& patientRecords) {
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