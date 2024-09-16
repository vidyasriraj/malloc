#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#pragma once
#include <cstddef>

struct FreeBlock {
    size_t size;
    FreeBlock* next;
};

class Allocator {
public:
    Allocator();
    ~Allocator();
    
    void* my_malloc(size_t size);
    void my_free(void* ptr);

private:
    FreeBlock* freeList;
};

#endif // ALLOCATOR_H
