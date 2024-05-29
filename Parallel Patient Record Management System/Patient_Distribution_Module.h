#ifndef PATIENT_DISTRIBUTION_MODULE_H
#define PATIENT_DISTRIBUTION_MODULE_H

#include <vector>
#include <string>

using namespace std;
class Patient_Distribution_Module {
public:
    Patient_Distribution_Module();
    ~Patient_Distribution_Module();
    void execute();

    void distributePatientRecords(const vector<string>& patientRecords);
    void readPatientRecordsFromFile(const string& filename, vector<string>& patientRecords);
};

#endif // PATIENT_DISTRIBUTION_MODULE_H
