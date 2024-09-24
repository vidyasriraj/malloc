#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "allocator.h"

MemoryAllocator::MemoryAllocator() {
}

// Destructor: Free the memory pool
MemoryAllocator::~MemoryAllocator() {
   
}

// Function to initialize the memory allocator
void MemoryAllocator::allocator_init() {
    memoryPool = std::malloc(POOL_SIZE);
    freeList = nullptr;
    allocatedSize = 0;

    if (!memoryPool) {
        std::fprintf(stderr, "Failed to allocate memory pool\n");
        std::exit(EXIT_FAILURE);
    }
}

// Custom malloc: Check the free list, allocate from pool if necessary
void* MemoryAllocator::my_malloc(size_t size) {
    if (size == 0) return nullptr;
    FreeBlock* prev = nullptr;
    FreeBlock* current = freeList;

    // Search the free list for a suitable block
    while (current) {
        if (current->size >= size) {
            // If block is large enough, split it if necessary
            if (current->size > size + sizeof(FreeBlock)) {
                FreeBlock* newBlock = (FreeBlock*)((char*)current + sizeof(FreeBlock) + size);
                newBlock->size = current->size - size - sizeof(FreeBlock);
                newBlock->next = current->next;

                if (prev) {
                    prev->next = newBlock;
                } else {
                    freeList = newBlock;
                }
            } else {
                // Remove the block from the free list if perfectly sized
                if (prev) {
                    prev->next = current->next;
                } else {
                    freeList = current->next;
                }
            }
            return (void*)((char*)current + sizeof(FreeBlock)); // Return usable memory pointer
        }
        prev = current;
        current = current->next;
    }

    // If no suitable block is found in the free list, allocate from the memory pool
    if (allocatedSize + size + sizeof(FreeBlock) > POOL_SIZE) {
        return nullptr;  // Not enough space in the pool
    }

    void* ptr = (char*)memoryPool + allocatedSize;
    allocatedSize += size + sizeof(FreeBlock);
    
    FreeBlock* newBlock = (FreeBlock*)ptr;
    newBlock->size = size;  // Set the size of the new block
    
    return (void*)((char*)newBlock + sizeof(FreeBlock)); // Return pointer to usable memory
}


// Custom realloc: Allocates new memory, copies content, and frees the old block
void* MemoryAllocator::my_realloc(void* ptr, size_t newSize) {
    if (!ptr) return my_malloc(newSize);  // Allocate if NULL ptr
    if (newSize == 0) {
        my_free(ptr); // Free if new size is 0
        return nullptr;
    }

    // Get the current block size
    FreeBlock* oldBlock = (FreeBlock*)((char*)ptr - sizeof(FreeBlock));
    size_t oldSize = oldBlock->size;

    // If the new size is less than or equal to the old size, just return the old pointer
    if (newSize <= oldSize) {
        return ptr;
    }

    // Allocate new memory, copy the data, and free the old memory
    void* newPtr = my_malloc(newSize);
    if (newPtr) {
        std::memcpy(newPtr, ptr, oldSize);  // Copy the data to the new block
        my_free(ptr);                       // Free the old block
    }
    return newPtr;
}


// Custom free: Adds the freed block to the free list
void MemoryAllocator::my_free(void* ptr) {
    if (!ptr) return;

    // Correctly adjust to get the FreeBlock
    FreeBlock* block = (FreeBlock*)((char*)ptr - sizeof(FreeBlock));

    // Add the freed block to the free list
    block->next = freeList;
    freeList = block; // Insert at the beginning of the free list
}



// Function to destroy the memory allocator and free the pool
void MemoryAllocator::allocator_destroy() {
    if (memoryPool != nullptr) {
        
        free(memoryPool);
        memoryPool = nullptr;  
    }
    freeList = nullptr; 
}

