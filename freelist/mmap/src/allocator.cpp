#include "allocator.h"
#include <unistd.h>  // For sbrk
#include <sys/mman.h>
#include <iostream>


Allocator::Allocator() : freeList(nullptr) {}

Allocator::~Allocator() {
}

void* Allocator::my_malloc(size_t size) {
    FreeBlock* prev = nullptr;
    FreeBlock* curr = freeList;

    // Find a block large enough in the free list
    while (curr) {
        if (curr->size >= size) {
            // Remove block from free list
            if (prev) {
                prev->next = curr->next;
            } else {
                freeList = curr->next;
            }
            return (void*)(curr + 1); // Return memory after the FreeBlock header
        }
        prev = curr;
        curr = curr->next;
    }

    // No suitable block found, use mmap to allocate more memory
    size_t totalSize = size + sizeof(FreeBlock); // Include space for the block header
    // totalSize = (totalSize + getpagesize() - 1) & ~(getpagesize() - 1); // Align to page size
    FreeBlock* block = (FreeBlock*)mmap(nullptr, totalSize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (block == MAP_FAILED) {
        std::cerr << "mmap failed: " << errno << std::endl;
        return nullptr;
    }

    block->size = totalSize; // Store the total size, including the header
    return (void*)(block + 1); // Return memory after the FreeBlock header
}

void Allocator::my_free(void* ptr) {
    if (!ptr) return;

    // Get the block header (which is located just before the memory returned to the user)
    FreeBlock* block = (FreeBlock*)ptr - 1;

    // Optionally, add the block back to the free list
    // block->next = freeList;
    // freeList = block;

    // Unmap the memory using the exact size stored in the block header
    if (munmap(block, block->size) == -1) {
        std::cerr << "munmap failed: " << errno << std::endl;
    }
}