#include "src/allocator.h"
#include <chrono>
#include <iostream>
#include <vector>

Allocator allocator;

int main() {
    allocator.init();
    // For accurate timing
    using clock = std::chrono::high_resolution_clock;
    auto start = clock::now();

    void* ptr1 = allocator.my_malloc(1024); // Allocate 1024 bytes
    allocator.my_free(ptr1); 
    void* ptr2 = allocator.my_malloc(256); 
    
    if(ptr1 == ptr2) {
        std::cout << "true\n"; 
    }
    allocator.my_free(ptr2);
    void* ptr3 = allocator.my_malloc(1024); 
     if(ptr1 == ptr3) {
        std::cout << "true\n"; 
    }
    allocator.my_free(ptr3);
    
    auto end = clock::now();
    std::cout << "Time: "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()
              << " ns\n";
    
    allocator.cleanup();

    return 0;
}
