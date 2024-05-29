#include "Parallel_Compression_Decompression_Module.h"
#include <iostream>
#include <vector>
#include <mpi.h>

using namespace std;

Parallel_Compression_Decompression_Module::Parallel_Compression_Decompression_Module() {}

Parallel_Compression_Decompression_Module::~Parallel_Compression_Decompression_Module() {}

void Parallel_Compression_Decompression_Module::execute() {
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 0) {
        compressAndDecompress();
    }
}

void Parallel_Compression_Decompression_Module::compressAndDecompress() {
    // Placeholder data
    vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> compressedData;
    vector<int> decompressedData;

    // Scatter data to all processes
    int data_size = data.size();
    MPI_Bcast(&data_size, 1, MPI_INT, 0, MPI_COMM_WORLD); // Broadcast data size
    vector<int> local_data(data_size);
    MPI_Scatter(data.data(), data_size, MPI_INT, local_data.data(), data_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Placeholder compression (each process compresses its local data)
    // Replace this with your actual compression algorithm
    for (int i = 0; i < data_size; ++i) {
        // Compress local data
        compressedData.push_back(local_data[i] * 2); // Example compression: double each element
    }

    // Gather compressed data from all processes
    vector<int> global_compressedData(data_size * MPI_COMM_WORLD); // Corrected MPI_COMM_WORLD
    MPI_Gather(compressedData.data(), data_size, MPI_INT, global_compressedData.data(), data_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Placeholder decompression (each process decompresses its portion of the data)
    // Replace this with your actual decompression algorithm
    decompressedData.resize(data_size);
    for (int i = 0; i < data_size; ++i) {
        // Decompress local data
        decompressedData[i] = global_compressedData[i] / 2; // Example decompression: halve each element
    }

    // Gather decompressed data from all processes
    vector<int> global_decompressedData(data_size * MPI_COMM_WORLD); // Corrected MPI_COMM_WORLD
    MPI_Gather(decompressedData.data(), data_size, MPI_INT, global_decompressedData.data(), data_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Output results on the root process (rank 0)
    if (MPI_COMM_WORLD == 0) { // Corrected MPI_COMM_WORLD
        // Display original and decompressed data
        cout << "Original data: ";
        for (int d : data) {
            cout << d << " ";
        }
        cout << endl;

        cout << "Decompressed data: ";
        for (int d : global_decompressedData) {
            cout << d << " ";
        }
        cout << endl;
    }
}
