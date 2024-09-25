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
    // For accurate timing
    allocator.init();
    using clock = std::chrono::high_resolution_clock;



    // 200 random allocations
    std::vector<void*> random_allocations;
    auto start = clock::now();
    for (int i = 0; i < 2000; ++i) {
        size_t alloc_size = get_random_size(16, 1024 * 1024);  // Between 256 bytes and 1 MB
        void* ptr = allocator.my_malloc(alloc_size);
        random_allocations.push_back(ptr);
    }
    auto end = clock::now();
    std::cout << "Time for 200 random allocations: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";

    start = clock::now();
    for (void* ptr : random_allocations) {
        allocator.my_free(ptr);
    }
    end = clock::now();
    std::cout << "Time for freeing 200 random allocations: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms\n";


    allocator.cleanup();
    return 0;
}
