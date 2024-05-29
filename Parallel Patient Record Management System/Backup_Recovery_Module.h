#ifndef BACKUP_RECOVERY_MODULE_H
#define BACKUP_RECOVERY_MODULE_H

#include <vector>
#include <string>

class Backup_Recovery_Module {
public:
    Backup_Recovery_Module();
    ~Backup_Recovery_Module();
    void execute();

    void backupPatientRecords(const std::string& fileName);
    void recoverPatientRecords(const std::string& fileName);
    void readPatientRecordsFromFile(const string& filename, vector<string>& patientRecords);
};

#endif // BACKUP_RECOVERY_MODULE_H
