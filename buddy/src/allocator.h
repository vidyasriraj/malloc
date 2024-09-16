#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>
#include <unistd.h>

struct BuddyBlock {
    size_t size;    // Size of the block (always a power of two)
    bool free;      // True if the block is free
    BuddyBlock* next;   // Pointer to the next free block in the list
    BuddyBlock* buddy;  // Pointer to the buddy block
};

class Allocator {
public:
    Allocator();
    ~Allocator();

    void* my_malloc(size_t size); // Allocate memory
    void my_free(void* ptr);      // Free memory

private:
    BuddyBlock* free_list;        // Pointer to the head of the free list

    size_t check_power_2(size_t size);  // Get the next power of two
    BuddyBlock* find_free_block(size_t size);   // Find a free block of at least size
    BuddyBlock* split_block(BuddyBlock* block, size_t size);  // Split a block into smaller sizes
    void add_to_free_list(BuddyBlock* block);   // Add block to the free list
    void merge_with_buddy(BuddyBlock* block); // Try to merge with buddy block
};

#endif // ALLOCATOR_H
