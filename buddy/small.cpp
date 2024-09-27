#include "src/allocator.h"
#include <chrono>
#include <iostream>
#include <vector>

Allocator allocator;

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
         if (ptr == nullptr) {
            std::cerr << "Allocation failed at iteration " << i << "\n";
            break;
        }
        small_allocations.push_back(ptr);
    }
    auto end = clock::now();
    std::cout << "Time for 100,000 small allocations: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
              << " ns\n";

    start = clock::now();
    for (void* ptr : small_allocations) {
        allocator.my_free(ptr);
    }
    end = clock::now();
    std::cout << "Time for freeing 100,000 small allocations: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
              << " ns\n";

    small_allocations.clear();

    allocator.cleanup();

    std::vector<void*> small_allocations_malloc;

    start = clock::now();
    for (int i = 0; i < 100000; ++i) {
        void* ptr = malloc(small_size);
        if (ptr == nullptr) {
            std::cerr << "Allocation failed at iteration " << i << "\n";
            break;
        }
        small_allocations_malloc.push_back(ptr);
    }
    end = clock::now();
    std::cout << "Time for 100,000 small allocations malloc: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
              << " ns\n";

    start = clock::now();
    for (void* ptr : small_allocations_malloc) {
        free(ptr);
    }
    end = clock::now();
    std::cout << "Time for freeing 100,000 small allocations: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
              << " ns\n";
    small_allocations_malloc.clear();
   

    return 0;
}
