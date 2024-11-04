#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>
#include <unordered_map>
#include <mutex>
// BuddyBlock structure representing a memory block
struct BuddyBlock{
    size_t size;
    bool free;
    int offset; // New field to track left or right position

    BuddyBlock(size_t sz = 0, bool is_free = true)
        : size(sz), free(is_free) {}
};

class Allocator {
public:
    Allocator();
    ~Allocator();

    // Initialize the allocator
    void init();

    // Cleanup all allocated memory
    void cleanup();

    // Allocate memory of at least 'size' bytes
    void* my_malloc(size_t size);

    // Free previously allocated memory
    void my_free(void* ptr);

private:
    // Hash map to store free blocks with their address as the key
    std::unordered_map<size_t, BuddyBlock*> free_list_map;

    // Utility function: returns the next power of two greater than or equal to 'size'
    size_t check_power_2(size_t size);

    // Searches for a free block that can satisfy the memory request
    BuddyBlock* find_free_block(size_t size);

    // Splits a larger block into two smaller blocks until it matches the requested size
    BuddyBlock* split_block(BuddyBlock* block, size_t size);

    // Adds a block to the free list map
    void add_to_free_list(BuddyBlock* block);

    // Attempts to merge a block with its buddy if both are free
    void merge_with_buddy(BuddyBlock* block);
};

#endif // ALLOCATOR_H
