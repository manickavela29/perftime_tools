#include <iostream>
#include <chrono>
#include <ctime>
#include <unistd.h> // for sleep

typedef std::chrono::milliseconds ms;

// C-style timing function
double get_time() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1e-9;
}

// C-style timing function to get time in milliseconds
double get_time_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1e6;
}

int main() {
    // Start timing with chrono
    auto chrono_start = std::chrono::high_resolution_clock::now();
    
    // Start timing with clock_gettime (C-style)
    double c_start_v1 = get_time();
    double c_start_v2 = get_time_ms();
    // Sleep for 2 seconds
    std::cout << "Sleeping for 2 seconds..." << std::endl;
    sleep(2); 

    // Mid-point sleep for 1 second
    std::cout << "Sleeping for 1 second..." << std::endl;
    sleep(1); 

    // End timing with chrono
    auto chrono_end = std::chrono::high_resolution_clock::now();
    // End timing with clock_gettime (C-style)
    double c_end_v1 = get_time();
    double c_end_v2 = get_time_ms();

    std::chrono::duration<float> chrono_float_duration_v1 = chrono_end - chrono_start;
    std::chrono::duration<float,std::milli> chrono_float_duration_v2 = chrono_end - chrono_start;
    std::chrono::duration<double> chrono_double_duration_v1 = chrono_end - chrono_start;
    std::chrono::duration<double,std::milli> chrono_double_duration_v2 = chrono_end - chrono_start;



    // Print results
    std::cout <<"\n\nSeconds Comparison" << std::endl;
    std::cout <<"------------------\n";
    std::cout << "Time measured using clock_gettime: " << c_end_v1 - c_start_v1 << " seconds" << std::endl;
    std::cout << "Time measured using float std::chrono: " << chrono_float_duration_v1.count() << " seconds" << std::endl;
    std::cout << "Time measured using double std::chrono: " << chrono_double_duration_v1.count() << " seconds\n" << std::endl;

    std::cout <<"Milliseconds Comparison : " << std::endl;
    std::cout <<"------------------\n";
    std::cout << "Time measured using clock_gettime: " << c_end_v2 - c_start_v2 << " milliseconds" << std::endl;
    std::cout << "Time measured using float std::chrono: " << chrono_float_duration_v2.count() << " milliseconds" << std::endl;
    std::cout << "Time measured using double std::chrono: " << chrono_double_duration_v2.count() << " milliseconds   " << std::endl;

    return 0;
}