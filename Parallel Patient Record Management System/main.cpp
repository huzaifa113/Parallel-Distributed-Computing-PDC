// main.cpp
#include <mpi.h>
#include <iostream>
#include "Initialization_Configuration_Module.h"
#include "Patient_Distribution_Module.h"
#include "Implementing_Operations_Module.h"
#include "Backup_Recovery_Module.h"
#include "Distributed_Search_Module.h"
#include "Logging_Module.h"
#include "Load_Balancing_Module.h"
#include "Parallel_Compression_Decompression_Module.h"


using namespace std;

void displayMenu() {
    cout << "Welcome to the Healthcare System!" << endl;
    cout << "1. Initialize and Configure System" << endl;
    cout << "2. Distribute Patient Records" << endl;
    cout << "3. Perform Operations on Patient Records" << endl;
    cout << "4. Search Patient Records" << endl;
    cout << "5. Perform Load Balancing" << endl;
    cout << "6. Perform Parallel Compression and Decompression" << endl;
    cout << "7. Backup and Recovery" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";
}

int main(int argc, char** argv) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    // Get the rank and size of the MPI communicator
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Initialize modules
    Initialization_Configuration_Module init_config_module;
    Patient_Distribution_Module patient_dist_module;
    Implementing_Operations_Module operations_module;
    Backup_Recovery_Module backup_recovery_module;
    Distributed_Search_Module search_module;
    Logging_Module logging_module;
    Load_Balancing_Module load_balancing_module;
    Parallel_Compression_Decompression_Module compression_decompression_module;


    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                init_config_module.execute();
                break;
            case 2:
                patient_dist_module.execute();
                break;
            case 3:
                operations_module.execute();
                break;
            case 4:
                search_module.execute();
                break;
            case 5:
                load_balancing_module.execute();
                break;
            case 6:
                compression_decompression_module.execute();
                break;
            case 7:
                backup_recovery_module.execute();
                break;
            case 8:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 9);

    // Finalize MPI
    MPI_Finalize();

    return 0;
}
