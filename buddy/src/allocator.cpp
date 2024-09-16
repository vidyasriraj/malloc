#include "allocator.h"
#include <cmath>
#include <cstring> 
#include <cstdlib> 

Allocator::Allocator() {
    free_list = nullptr;
}

Allocator::~Allocator() {
}


size_t Allocator::check_power_2(size_t size) {
    size_t power = 1;
    while (power < size) {
        power <<= 1; 
    }
    return power;
}

BuddyBlock* Allocator::find_free_block(size_t size) {
    BuddyBlock* prev = nullptr;
    BuddyBlock* curr = free_list;

    // Traverse the free list to find a free block of at least the requested size
    while (curr) {
        if (curr->free && curr->size >= size) {
            if (prev) {
                prev->next = curr->next;
            } else {
                free_list = curr->next;
            }
            curr->next = nullptr;
            curr->free = false;
            return curr;
        }
        prev = curr;
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

        add_to_free_list(buddy);  // Add the buddy block to the free list
    }

    return block;
}

void Allocator::add_to_free_list(BuddyBlock* block) {
    block->next = free_list;
    free_list = block;
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
        block = (BuddyBlock*)sbrk(block_size);
        block->size = block_size;
        block->free = false;
        block->buddy = nullptr;
        block->next = nullptr;
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
    block->free = true;

    // Try to merge the block with its buddy
    merge_with_buddy(block);

}

void Allocator::merge_with_buddy(BuddyBlock* block) {
    BuddyBlock* buddy = block->buddy;
    if (buddy && buddy->free && buddy->size == block->size) {
        // Remove buddy from free list
        BuddyBlock** curr = &free_list;
        while (*curr) {
            if (*curr == buddy) {
                *curr = buddy->next;
                break;
            }
            curr = &(*curr)->next;
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

