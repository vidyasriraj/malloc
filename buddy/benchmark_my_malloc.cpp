#include "src/allocator.h"
#include <benchmark/benchmark.h>
#include <cstdlib>  // For malloc and free

Allocator allocator;

static void BM_SystemMalloc(benchmark::State& state) {
    for (auto _ : state) {
        // Perform a single allocation and deallocation cycle
        void* ptr = malloc(256);
        if (ptr) {
            free(ptr);
        }
        
        ptr = malloc(8);
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



BENCHMARK_MAIN();
