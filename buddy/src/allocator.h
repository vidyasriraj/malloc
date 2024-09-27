#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>
#include <unistd.h>

// BuddyBlock structure representing a memory block
struct BuddyBlock {
    size_t size;           // Size of the block
    bool free;             // Whether the block is free or not
    BuddyBlock* next;      // Pointer to the next block in the list
    BuddyBlock* prev;      // Pointer to the previous block in the list
    BuddyBlock* buddy;     // Pointer to the buddy block
};

class Allocator {
public:
    Allocator();
    ~Allocator();
    void init();
    void cleanup();
    BuddyBlock* free_list;  
    
    void* my_malloc(size_t size);
    void my_free(void* ptr);

private:
         // Pointer to the head of the free list
   
    // Utility function: returns the next power of two greater than or equal to 'size'
    size_t check_power_2(size_t size);

    // Searches for a free block that can satisfy the memory request
    BuddyBlock* find_free_block(size_t size);

    // Splits a larger block into two smaller blocks until it matches the requested size
    BuddyBlock* split_block(BuddyBlock* block, size_t size);

    // Adds a block to the free list
    void add_to_free_list(BuddyBlock* block);

    // Attempts to merge a block with its buddy if both are free
    void merge_with_buddy(BuddyBlock* block);
};

#endif // ALLOCATOR_H
