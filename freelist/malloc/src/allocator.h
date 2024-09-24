#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>

#define POOL_SIZE (128 * 1024 * 1024)  // 128 MB

// Structure to represent a free block in the free list
struct FreeBlock {
    size_t size;              
    FreeBlock* next;          
};

// Memory Allocator class to manage the memory pool
class MemoryAllocator {
private:
    void* memoryPool;        

public:
    
    MemoryAllocator();
    ~MemoryAllocator();

    FreeBlock* freeList;
    size_t allocatedSize;  
    void* my_malloc(size_t size);
    void* my_realloc(void* ptr, size_t newSize);
    void my_free(void* ptr);
    void allocator_init();
    void allocator_destroy();
};

#endif // ALLOCATOR_H
