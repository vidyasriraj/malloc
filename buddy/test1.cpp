#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>
#include "src/allocator.h"

Allocator allocator;

void random_allocations_and_deallocations(int iterations, size_t size, bool use_custom_allocator) {
    std::vector<void*> allocations;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> operation_distribution(0, 1); // 0 for allocation, 1 for deallocation

    for (int i = 0; i < iterations; ++i) {
        int operation = operation_distribution(generator);

        if (operation == 0) {
            void* ptr = use_custom_allocator ? allocator.my_malloc(size) : malloc(size);
            if (ptr) {
                allocations.push_back(ptr);
            }
        } else if (!allocations.empty()) {
            int index = generator() % allocations.size(); 
            void* ptr = allocations[index];
            if (use_custom_allocator) {
                allocator.my_free(ptr);
            } else {
                free(ptr);
            }
            allocations.erase(allocations.begin() + index); 
        }
    }

    // Free any remaining allocated blocks
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

    const int num_threads = 4;        
    const int iterations= 2500; 
    std::default_random_engine size;
    std::uniform_int_distribution<size_t> size_distribution(1, 1024); // Random sizes between 1 and 1024 bytes
    const size_t allocation_size = size_distribution(size);
    // Measure time for custom allocator
    auto start = clock::now();
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(random_allocations_and_deallocations, iterations, allocation_size, true);
    }
    for (auto& th : threads) {
        th.join();
    }
    auto end = clock::now();
    std::cout << "Time for " << num_threads * iterations
              << " random allocations and deallocations with custom allocator (multithreaded): "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    allocator.cleanup();

    // Measure time for malloc/free (standard allocator)
    start = clock::now();
    threads.clear();
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(random_allocations_and_deallocations, iterations, allocation_size, false);
    }
    for (auto& th : threads) {
        th.join();
    }
    end = clock::now();
    std::cout << "Time for " << num_threads * iterations
              << " random allocations and deallocations with malloc (multithreaded): "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    return 0;
}
