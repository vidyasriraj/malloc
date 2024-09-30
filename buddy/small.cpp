#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "src/allocator.h"

Allocator allocator;

void thread_allocations(int iterations, size_t size, bool use_custom_allocator) {
    std::vector<void*> allocations;
    
    for (int i = 0; i < iterations; ++i) {
        void* ptr = use_custom_allocator ? allocator.my_malloc(size) : malloc(size);
        allocations.push_back(ptr);
    }

    for (void* ptr : allocations) {
        if (use_custom_allocator) {
            allocator.my_free(ptr);
        } else {
            free(ptr);
        }
    }
}

int main() {
    allocator.init();
    using clock = std::chrono::high_resolution_clock;

    const int num_threads = 4;  // Number of threads
    const int iterations_per_thread = 2500;  
    const size_t small_size = 32;  // Size of each allocation
    
    // Measure time for custom allocator
    auto start = clock::now();
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(thread_allocations, iterations_per_thread, small_size, true);
    }
    for (auto& th : threads) {
        th.join();
    }
    auto end = clock::now();
    std::cout << "Time for " << num_threads * iterations_per_thread 
              << " small allocations with custom allocator (multithreaded): "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    allocator.cleanup();

    // Measure time for malloc/free (standard allocator)
    start = clock::now();
    threads.clear();
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(thread_allocations, iterations_per_thread, small_size, false);
    }
    for (auto& th : threads) {
        th.join();
    }
    end = clock::now();
    std::cout << "Time for " << num_threads * iterations_per_thread 
              << " small allocations with malloc (multithreaded): "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    return 0;
}
