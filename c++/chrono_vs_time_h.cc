#include <iostream>
#include <chrono>
#include <ctime>
#include <unistd.h> // for sleep

// C-style timing function
double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

int main() {
    // Start timing with chrono
    auto chrono_start = std::chrono::high_resolution_clock::now();
    
    // Start timing with clock_gettime (C-style)
    double c_start = get_time();

    // Sleep for 2 seconds
    std::cout << "Sleeping for 2 seconds..." << std::endl;
    sleep(2); 

    // Mid-point sleep for 1 second
    std::cout << "Sleeping for 1 second..." << std::endl;
    sleep(1); 

    // End timing with chrono
    auto chrono_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> chrono_duration = chrono_end - chrono_start;
    
    // End timing with clock_gettime (C-style)
    double c_end = get_time();

    // Print results
    std::cout << "\nTime measured using std::chrono: " << chrono_duration.count() << " seconds" << std::endl;
    std::cout << "Time measured using clock_gettime: " << c_end - c_start << " seconds" << std::endl;

    return 0;
}