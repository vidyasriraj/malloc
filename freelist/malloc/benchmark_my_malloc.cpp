#include "src/allocator.h"
#include <benchmark/benchmark.h>
#include <cstdlib>  // For malloc and free

MemoryAllocator allocator;

static void BM_SystemMalloc(benchmark::State& state) {
    for (auto _ : state) {
        // Perform a single allocation and deallocation cycle
        void* ptr = malloc(256);
        if (ptr) {
            free(ptr);
        }
        
        ptr = malloc(8);
        ptr = realloc(ptr,1024*1024);
        if (ptr) {
            free(ptr);
        }
        
        ptr = malloc(128);
        if (ptr) {
            free(ptr);
        }
    }
}
BENCHMARK(BM_SystemMalloc);

static void BM_CustomMalloc(benchmark::State& state) {
    for (auto _ : state) {
        // Perform a single allocation and deallocation cycle
        void* ptr = allocator.my_malloc(256);
        if (ptr) {
            allocator.my_free(ptr);
        }
        
        ptr = allocator.my_malloc(8);
        
        ptr = allocator.my_realloc(ptr,1024*1024);
        if (ptr) {
            allocator.my_free(ptr);
        }
        
        ptr = allocator.my_malloc(128);
        if (ptr) {
            allocator.my_free(ptr);
        }
    }
}
BENCHMARK(BM_CustomMalloc);


int main(int argc, char** argv) {
    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    allocator.allocator_destroy();
    return 0;
}
