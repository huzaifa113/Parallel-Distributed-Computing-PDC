#ifndef DISTRIBUTED_SEARCH_MODULE_H
#define DISTRIBUTED_SEARCH_MODULE_H

#include <vector>
#include <string>

using namespace std;
class Distributed_Search_Module {
public:
    Distributed_Search_Module();
    ~Distributed_Search_Module();
    void execute();
    void indexPatientRecords(const vector<string>& patientRecords);
    void readPatientRecordsFromFile(const string& filename, vector<string>& patientRecords);
    void searchPatientRecords(int world_rank, int searchIndex);
    void distributePatientRecords(const vector<string>& patientRecords, int world_rank);
    void indexAndSearchPatientRecords(int world_rank, int searchIndex, const vector<string>& patientRecords);
};

#endif // DISTRIBUTED_SEARCH_MODULE_H
