#include "src/allocator.h"
#include <chrono>
#include <iostream>
#include <vector>

Allocator allocator;

// Helper function to generate random sizes between min and max
size_t get_random_size(size_t min, size_t max) {
    return min + (rand() % (max - min + 1));
}

int main() {
    allocator.init();
    // For accurate timing
    using clock = std::chrono::high_resolution_clock;
    
    // 100,000 small, short-lived allocations
    std::vector<void*> small_allocations;
    size_t small_size = 32;  // Small allocations of 32 bytes
    auto start = clock::now();
    for (int i = 0; i < 100000; ++i) {
        void* ptr = allocator.my_malloc(small_size);
        small_allocations.push_back(ptr);
    }
    auto end = clock::now();
    std::cout << "Time for 100,000 small allocations: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    start = clock::now();
    for (void* ptr : small_allocations) {
        allocator.my_free(ptr);
    }
    end = clock::now();
    std::cout << "Time for freeing 100,000 small allocations: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";



    allocator.cleanup();
    

    return 0;
}
