#ifndef INITIALIZATION_CONFIGURATION_MODULE_H
#define INITIALIZATION_CONFIGURATION_MODULE_H

class Initialization_Configuration_Module {
public:
    Initialization_Configuration_Module();
    ~Initialization_Configuration_Module();
    void execute();
private:
    void initializeMPI();
    void parsePatientConfiguration();
    void establishMPICommunicators();
};

#endif // INITIALIZATION_CONFIGURATION_MODULE_H
