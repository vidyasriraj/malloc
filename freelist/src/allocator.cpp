#include "allocator.h"
#include <unistd.h>  // For sbrk

Allocator::Allocator() : freeList(nullptr) {}

Allocator::~Allocator() {
}

void* Allocator::my_malloc(size_t size) {
    FreeBlock* prev = nullptr;
    FreeBlock* curr = freeList;

    // Find a block large enough
    while (curr) {
        if (curr->size >= size) {
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

    // No suitable block found, so use system's sbrk to allocate more memory
    FreeBlock* block = (FreeBlock*)sbrk(size + sizeof(FreeBlock));
    if (block == (void*)-1) {  // sbrk failed
        return nullptr;
    }
    block->size = size;
    return (void*)(block + 1);  // Return memory after the FreeBlock header
}

void Allocator::my_free(void* ptr) {
    if (!ptr) return;

    FreeBlock* block = (FreeBlock*)ptr - 1;  // Get the block header
    block->next = freeList;
    freeList = block;
}
