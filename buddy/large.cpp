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

    // 2,000 allocations between 5MB and 25MB
    std::vector<void*> large_allocations;
    auto start = clock::now();
    for (int i = 0; i < 1000; ++i) {
        size_t alloc_size = get_random_size(5 * 1024 * 1024, 25 * 1024 * 1024);
        void* ptr = allocator.my_malloc(alloc_size);
        large_allocations.push_back(ptr);
    }

    auto end = clock::now();
    std::cout << "Time for 2,000 large allocations  "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    start = clock::now();
    for (void* ptr : large_allocations) {
        allocator.my_free(ptr);
    }
     end = clock::now();
    std::cout << "Time for freeing : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";


    allocator.cleanup();

    std::vector<void*> large_allocations_malloc;
    start = clock::now();
    for (int i = 0; i < 1000; ++i) {
        size_t alloc_size = get_random_size(5 * 1024 * 1024, 25 * 1024 * 1024);
        void* ptr = malloc(alloc_size);
        large_allocations_malloc.push_back(ptr);
    }

    end = clock::now();
    std::cout << "Time for 2,000 large allocations  "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    start = clock::now();
    for (void* ptr : large_allocations_malloc) {
        free(ptr);
    }
     end = clock::now();
    std::cout << "Time for freeing : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    return 0;
}
