#include "gtest/gtest.h"
#include "../src/allocator.h"

class AllocatorTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Allocator allocator;
};

// Test case for large allocation
TEST_F(AllocatorTest, LargeAllocation) {
    // Allocate a large chunk of memory (e.g., 1 MB)
    void* ptr = allocator.my_malloc(1024 * 1024);
    EXPECT_NE(ptr, nullptr);
    allocator.my_free(ptr);
}

// Test case for many small allocations
TEST_F(AllocatorTest, ManySmallAllocations) {
    const int allocCount = 10000;
    void* ptrs[allocCount];

    // Allocate many small blocks of 32 bytes
    for (int i = 0; i < allocCount; ++i) {
        ptrs[i] = allocator.my_malloc(32);
        EXPECT_NE(ptrs[i], nullptr);
    }

    // Free the allocated memory
    for (int i = 0; i < allocCount; ++i) {
        allocator.my_free(ptrs[i]);
    }
}

// Test case for fragmentation handling and coalescing
TEST_F(AllocatorTest, MemoryFragmentationAndCoalescing) {
    // Allocate and free memory in a pattern that creates fragmentation
    void* ptr1 = allocator.my_malloc(60);
    void* ptr2 = allocator.my_malloc(1116);
    void* ptr3 = allocator.my_malloc(74);

    // Free the middle block
    allocator.my_free(ptr2);

    // Allocate a block of the same size as the freed middle block
    void* ptr4 = allocator.my_malloc(1113);
    EXPECT_EQ(ptr2, ptr4);  // Check if the same block was reused

    allocator.my_free(ptr1);
    allocator.my_free(ptr3);
    allocator.my_free(ptr4);
}

// Test case for alignment of allocations
TEST_F(AllocatorTest, AllocationAlignment) {
    void* ptr1 = allocator.my_malloc(13);
    void* ptr2 = allocator.my_malloc(30);
    void* ptr3 = allocator.my_malloc(49);

    // Check that all returned addresses are aligned to at least 8 bytes
    EXPECT_EQ((reinterpret_cast<uintptr_t>(ptr1) % 8), 0);
    EXPECT_EQ((reinterpret_cast<uintptr_t>(ptr2) % 8), 0);
    EXPECT_EQ((reinterpret_cast<uintptr_t>(ptr3) % 8), 0);

    allocator.my_free(ptr1);
    allocator.my_free(ptr2);
    allocator.my_free(ptr3);
}


// Test case for checking memory reuse
TEST_F(AllocatorTest, MemoryReuse) {
    void* ptr1 = allocator.my_malloc(1228);
    allocator.my_free(ptr1);

    // Allocate a new block of the same size
    void* ptr2 = allocator.my_malloc(1228);
    EXPECT_EQ(ptr1, ptr2);  // Check if the same block was reused

    allocator.my_free(ptr2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
