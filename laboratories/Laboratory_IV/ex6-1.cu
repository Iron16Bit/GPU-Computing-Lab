#include <iostream>
#include <cuda_runtime.h>

int main() {
    int deviceCount = 0;
    cudaGetDeviceCount(&deviceCount);

    for (int device = 0; device < deviceCount; ++device) {
        cudaDeviceProp prop;
        cudaGetDeviceProperties(&prop, device);

        // Memory Clock Rate in kHz, convert to Hz
        double memClockHz = static_cast<double>(prop.memoryClockRate) * 1000.0;

        // Bus Width in bits → convert to bytes
        double busWidthBytes = static_cast<double>(prop.memoryBusWidth) / 8.0;

        // Theoretical memory bandwidth in GB/s
        double bandwidthGBs = (2.0 * memClockHz * busWidthBytes) / 1e9;

        std::cout << "Device " << device << ": " << prop.name << std::endl;
        std::cout << "  Compute capability: " << prop.major << "." << prop.minor << std::endl;
        std::cout << "  Total global memory: " << prop.totalGlobalMem / (1024 * 1024) << " MB" << std::endl;
        std::cout << "  Multiprocessors: " << prop.multiProcessorCount << std::endl;
        std::cout << "  Memory Clock Rate: " << prop.memoryClockRate / 1000 << " MHz" << std::endl;
        std::cout << "  Memory Bus Width: " << prop.memoryBusWidth << " bits" << std::endl;
        std::cout << "  Theoretical Memory Bandwidth: " << bandwidthGBs << " GB/s" << std::endl;
        std::cout << std::endl;
    }

    return 0;
}