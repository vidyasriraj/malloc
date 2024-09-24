#include <gtest/gtest.h>
#include "../src/allocator.h"
#include <cstring>  // For memcpy and memcmp

class MemoryAllocatorTest : public ::testing::Test {
protected:
    MemoryAllocator allocator;

    void SetUp() override {
        allocator.allocator_init();
    }

    void TearDown() override {
        // Destroy the allocator after each test (handled by destructor)
    }
};

TEST_F(MemoryAllocatorTest, BasicAllocation) {
    void* ptr = allocator.my_malloc(128);
    EXPECT_NE(ptr, nullptr);
    allocator.my_free(ptr);
}

TEST_F(MemoryAllocatorTest, ZeroAllocation) {
    void* ptr = allocator.my_malloc(0);
    EXPECT_EQ(ptr, nullptr);  // Assuming you return nullptr for zero allocation
}

TEST_F(MemoryAllocatorTest, ReallocatingNullPointer) {
    void* ptr = allocator.my_realloc(nullptr, 100);
    EXPECT_NE(ptr, nullptr);
    allocator.my_free(ptr);
}

TEST_F(MemoryAllocatorTest, ReallocatingZeroSize) {
    void* ptr = allocator.my_malloc(100);
    void* newPtr = allocator.my_realloc(ptr, 0);
    EXPECT_EQ(newPtr, nullptr);
    allocator.my_free(ptr);
    allocator.my_free(newPtr);
}

TEST_F(MemoryAllocatorTest, FreeingNullPointer) {
    EXPECT_NO_THROW(allocator.my_free(nullptr));  // Freeing nullptr should not throw
}

TEST_F(MemoryAllocatorTest, Fragmentation) {
    void* ptr1 = allocator.my_malloc(100);
    void* ptr2 = allocator.my_malloc(200);
    allocator.my_free(ptr1);
    void* ptr3 = allocator.my_malloc(50);
    EXPECT_NE(ptr3, nullptr);
    allocator.my_free(ptr2);
    allocator.my_free(ptr3);
}

TEST_F(MemoryAllocatorTest, LargeAllocation) {
    void* ptr = allocator.my_malloc(POOL_SIZE + 1);
    EXPECT_EQ(ptr, nullptr);  // Should return nullptr if exceeding pool size
    allocator.my_free(ptr);
}

TEST_F(MemoryAllocatorTest, SplittingBlocks) {
    void* ptr1 = allocator.my_malloc(200);
    void* ptr2 = allocator.my_malloc(100);
    allocator.my_free(ptr1);
    allocator.my_free(ptr2);
    
    void* ptr3 = allocator.my_malloc(50);  // Should use the freed block
    EXPECT_EQ(ptr3, ptr2);
    allocator.my_free(ptr3);
}



TEST_F(MemoryAllocatorTest, ReallocatingLargerSize) {
    void* ptr1 = allocator.my_malloc(100);
    void* ptr2 = allocator.my_realloc(ptr1, 200);
    EXPECT_NE(ptr2, nullptr);
    EXPECT_NE(ptr2, ptr1);  // Ensure it returns a new pointer
    allocator.my_free(ptr2);
    allocator.my_free(ptr1);
}

TEST_F(MemoryAllocatorTest, ReallocatingSmallerSize) {
    void* ptr1 = allocator.my_malloc(200);
    void* ptr2 = allocator.my_realloc(ptr1, 100);
    EXPECT_EQ(ptr2, ptr1);  // Should return the same pointer if it shrinks
    allocator.my_free(ptr2);
    allocator.my_free(ptr1);
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}
