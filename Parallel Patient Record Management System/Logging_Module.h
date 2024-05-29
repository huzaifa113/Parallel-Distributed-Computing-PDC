#ifndef LOGGING_MODULE_H
#define LOGGING_MODULE_H

#include <string>

class Logging_Module {
public:
    Logging_Module();
    ~Logging_Module();
    void logOperation(const std::string& operation);
    void logError(const std::string& error);
    void log(const std::string& type, const std::string& message);
};

#endif // LOGGING_MODULE_H
