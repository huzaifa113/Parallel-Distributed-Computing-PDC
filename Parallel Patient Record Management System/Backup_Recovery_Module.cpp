
#include "Backup_Recovery_Module.h"
#include "Logging_Module.h"
#include <iostream>
#include <fstream>
#include <mpi.h>

using namespace std;

void readPatientRecordsFromFile(const string& filename, vector<string>& patientRecords);
Logging_Module loggingModule;

void Backup_Recovery_Module::execute() {
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Read patient records from files
    vector<string> patientRecords;
    readPatientRecordsFromFile("Patient_Records.txt", patientRecords);
    readPatientRecordsFromFile("Additional_Patient_Records.txt", patientRecords);
    readPatientRecordsFromFile("Extra_Patient_Records.txt", patientRecords);

    int choice;
    string fileName;
    cout<<"1) Make Backup: " << endl;
    cout<<"2) Restore Backup: " << endl;
    cout<<"Enter Your Choice: " << endl;
    cin>>choice;

    switch (choice) {
        case 1:
            cout << "Enter the name of the file to backup: ";
            std::getline(std::cin, fileName);
            backupPatientRecords(fileName);
            break;

        case 2:
            cout << "Enter the name of the backup file to restore: ";
            std::getline(std::cin, fileName);
            recoverPatientRecords(fileName);
            break;

        default:
            cout << "Invalid choice. Please enter a number between 1 and 2." << endl;
            break;
    }

}
void Backup_Recovery_Module::backupPatientRecords(const std::string& fileName) {
    // Open the input file
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file for backup." << std::endl;
        return;
    }

    // Create a backup file
    std::ofstream backupFile("backup.txt");
    if (!backupFile.is_open()) {
        std::cerr << "Error: Unable to create backup file." << std::endl;
        inputFile.close(); // Close the input file
        return;
    }

    // Read the contents of the input file and write them to the backup file
    std::string line;
    while (std::getline(inputFile, line)) {
        backupFile << line << std::endl;
    }

    // Close the files
    inputFile.close();
    backupFile.close();

    cout << "Backup completed successfully." << endl;

    string logMessage = "Backed Up record with  " + fileName;
    loggingModule.logOperation(logMessage);
}


void Backup_Recovery_Module::recoverPatientRecords(const std::string& fileName) {
    // Open the backup file
    std::ifstream backupFile(fileName);
    if (!backupFile.is_open()) {
        std::cerr << "Error: Unable to open backup file." << std::endl;
        return;
    }

    // Read patient records from the backup file and restore them
    std::string line;
    while (std::getline(backupFile, line)) {
        // Restore each record (you can store them in your database)
        // Example: database.insert(line);
        std::cout << "Restored record: " << line << std::endl;
    }
    backupFile.close();

    std::cout << "Recovery completed successfully." << std::endl;

    string logMessage = "Restored record with  " + fileName;
    loggingModule.logOperation(logMessage);
}


void Backup_Recovery_Module::readPatientRecordsFromFile(const string& filename, vector<string>& patientRecords) {
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