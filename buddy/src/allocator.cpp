#include "allocator.h"
#include <unordered_map>
#include <cstdlib>

std::mutex allocator_mutex;  

Allocator::Allocator() {
}

Allocator::~Allocator() {   
}

void Allocator::init() {
    free_list_map.clear();
}

void Allocator::cleanup() {
    for (auto& entry : free_list_map) {
        free(entry.second);
    }
    free_list_map.clear();
    
}

size_t Allocator::check_power_2(size_t size) {
    size_t power = 1;
    while (power < size) {
        power <<= 1; 
    }
    return power;
}

BuddyBlock* Allocator::find_free_block(size_t size) {
    BuddyBlock* suitable_block = nullptr;
    size_t suitable_size = 0;

    // Iterate over the hash map to find the smallest suitable block
    for (auto& entry : free_list_map) {
        BuddyBlock* block = entry.second;
        if ( block->size >= size) {
            if (!suitable_block || block->size < suitable_size) {
                suitable_block = block;
                suitable_size = block->size;
            }
        }
    }

    if (suitable_block) {
        free_list_map.erase((size_t)suitable_block);
        suitable_block->free = false;
        return suitable_block;
    }
    return nullptr;
}

BuddyBlock* Allocator::split_block(BuddyBlock* block, size_t size) {
    while (block->size > size) {
        block->size /= 2;
        BuddyBlock* buddy = (BuddyBlock*)((char*)block + block->size);
        buddy->size = block->size;
        buddy->free = true;
        buddy->buddy = block;
        block->buddy = buddy;
        add_to_free_list(buddy);
    }

    return block;
}

void Allocator::add_to_free_list(BuddyBlock* block) {
    size_t key = (size_t)block;
    free_list_map[key] = block;
}

void* Allocator::my_malloc(size_t size) {
    std::lock_guard<std::mutex> lock(allocator_mutex);
    if (size == 0) {
        return nullptr; 
    }

    size_t total_size = check_power_2(size + sizeof(BuddyBlock));
    BuddyBlock* block = find_free_block(total_size);

    if (!block) {
        block = (BuddyBlock*)malloc(total_size);
        if (!block) {
            return nullptr; 
        }
        block->size = total_size;
        block->free = false;
        block->buddy = nullptr;
    } else {
        block = split_block(block, total_size);
    }

    return (void*)(block + 1);  
}

void Allocator::my_free(void* ptr) {
    std::lock_guard<std::mutex> lock(allocator_mutex);
    if (!ptr) return;

    BuddyBlock* block = (BuddyBlock*)((char*)ptr - sizeof(BuddyBlock));
    if (block->free) {
        return;  
    }

    block->free = true;
    add_to_free_list(block);

    merge_with_buddy(block);
}

void Allocator::merge_with_buddy(BuddyBlock* block) {
    size_t buddy_address = (size_t)block ^ block->size;  // XOR to find buddy address

    // Check if the buddy exists in the hash map
    auto it = free_list_map.find(buddy_address);
    if (it != free_list_map.end()) {
        BuddyBlock* buddy = it->second;

        // Remove buddy from the map
        free_list_map.erase(it);

        // Merge blocks
        block->size *= 2;
        merge_with_buddy(block);  
    } else {
        add_to_free_list(block);
    }
}