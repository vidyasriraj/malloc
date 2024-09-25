#include "allocator.h"
#include <cmath>
#include <cstring> 
#include <cstdlib> 

Allocator::Allocator() {
   
}

Allocator::~Allocator() {
 
}

void Allocator::init() {
    free_list = nullptr;
    allocated_list = nullptr;
}


void Allocator::cleanup() {
    BuddyBlock* curr = allocated_list;
    while (curr) {
        BuddyBlock* next = curr->next;
        
        // Free only if the block is not already free
        if (!curr->free) {
            free(curr);
        }
        curr = next;
    }

    // Ensure the free list is also cleaned up
    curr = free_list;
    while (curr) {
        BuddyBlock* next = curr->next;
        free(curr);
        curr = next;
    }

    free_list = nullptr;
    allocated_list = nullptr;
}

size_t Allocator::check_power_2(size_t size) {
    size_t power = 1;
    while (power < size) {
        power <<= 1; 
    }
    return power;
}

BuddyBlock* Allocator::find_free_block(size_t size) {
    BuddyBlock* curr = free_list;

    while (curr) {
        if (curr->free && curr->size >= size) {
            if (curr->prev) {
                curr->prev->next = curr->next;
            } else {
                free_list = curr->next;
            }
            if (curr->next) {
                curr->next->prev = curr->prev;
            }

            curr->next = nullptr;
            curr->prev = nullptr;
            curr->free = false;
            return curr;
        }
        curr = curr->next;
    }

    // No suitable block found, return nullptr
    return nullptr;
}

BuddyBlock* Allocator::split_block(BuddyBlock* block, size_t size) {
    // Split the block until the block's size matches the requested size
    while (block->size > size) {
        block->size /= 2;

        BuddyBlock* buddy = (BuddyBlock*)((char*)block + block->size);
        buddy->size = block->size;
        buddy->free = true;
        buddy->buddy = block;
        block->buddy = buddy;
        buddy->next = nullptr;
        buddy->prev = nullptr;

        add_to_free_list(buddy);  // Add the buddy block to the free list
    }

    return block;
}

void Allocator::add_to_free_list(BuddyBlock* block) {
    block->next = free_list;
    block->prev = nullptr;
    if (free_list) {
        free_list->prev = block;
    }
    free_list = block;
}

void Allocator::add_to_allocated_list(BuddyBlock* block) {
    block->next = allocated_list;
    block->prev = nullptr;
    if (allocated_list) {
        allocated_list->prev = block;
    }
    allocated_list = block;
}

void* Allocator::my_malloc(size_t size) {
    if (size == 0) {
        return nullptr;  // Cannot allocate zero-sized block
    }

    // Add header size to the allocation request
    size_t block_size = check_power_2(size + sizeof(BuddyBlock));
    BuddyBlock* block = find_free_block(block_size);

    // If no free block is found, request more memory from the system
    if (!block) {
        block = (BuddyBlock*)malloc(block_size);
        block->size = block_size;
        block->free = false;
        block->buddy = nullptr;
        block->next = nullptr;
        block->prev = nullptr;

        // Add the newly allocated block to the allocated list
        add_to_allocated_list(block);
    } else {
        // If a larger block is found, split it to the requested size
        block = split_block(block, block_size);
    }

    return (void*)(block + 1);  // Return memory after the block header
}

void Allocator::my_free(void* ptr) {
    if (!ptr) return;

    // Get the block header
    BuddyBlock* block = (BuddyBlock*)ptr - 1;
    if (block->free) {
        return;  // Avoid double-freeing
    }
    
    block->free = true;

    // Try to merge the block with its buddy
    merge_with_buddy(block);
}

void Allocator::merge_with_buddy(BuddyBlock* block) {
    BuddyBlock* buddy = block->buddy;
    if (buddy && buddy->free && buddy->size == block->size) {
        // Remove buddy from free list
        if (buddy->prev) {
            buddy->prev->next = buddy->next;
        } else {
            free_list = buddy->next;
        }
        if (buddy->next) {
            buddy->next->prev = buddy->prev;
        }

        // Merge blocks
        block->size *= 2;
        block->buddy = nullptr;
        buddy->buddy = nullptr;

        // Try to merge the new larger block with its buddy
        merge_with_buddy(block);
    } else {
        // Add the block back to the free list if no merging happens
        add_to_free_list(block);
    }
}
