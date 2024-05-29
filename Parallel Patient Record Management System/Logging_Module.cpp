#include "Logging_Module.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

using namespace std;

Logging_Module::Logging_Module() {}

Logging_Module::~Logging_Module() {}

void Logging_Module::logOperation(const string& operation) {
    log("Operation", operation);
}

void Logging_Module::logError(const string& error) {
    log("Error", error);
}

void Logging_Module::log(const string& type, const string& message) {
    // Get current time
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    // Convert time to string
    string timeStr = ctime(&now_time);
    timeStr.pop_back(); // Remove newline character

    // Open log file in append mode
    ofstream logFile("log.txt", ios_base::app);
    if (!logFile) {
        cerr << "Error: Unable to open log file." << endl;
        return;
    }

    // Write log entry
    logFile << "[" << type << "][" << timeStr << "]: " << message << endl;
    logFile.close();
}
