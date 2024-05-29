#ifndef LOAD_BALANCING_MODULE_H
#define LOAD_BALANCING_MODULE_H

class Load_Balancing_Module {
public:
    Load_Balancing_Module();
    ~Load_Balancing_Module();
    void execute();
private:
    void balanceLoad(int world_size);
    // Add any additional private member functions or variables as needed
};

#endif // LOAD_BALANCING_MODULE_H
