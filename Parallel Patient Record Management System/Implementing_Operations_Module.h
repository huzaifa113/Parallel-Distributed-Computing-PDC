#ifndef IMPLEMENTING_OPERATIONS_MODULE_H
#define IMPLEMENTING_OPERATIONS_MODULE_H

#include <vector>
#include <string>

class Implementing_Operations_Module {
public:
    Implementing_Operations_Module();
    ~Implementing_Operations_Module();
    void execute();

    void addPatientRecord(const std::string& record);
    void updatePatientRecord(const std::string& record);
    void deletePatientRecord(const std::string& recordID);
    void readPatientRecords();
    void readPatientRecordsFromFile(const string& filename, vector<string>& patientRecords);
};

#endif // IMPLEMENTING_OPERATIONS_MODULE_H
