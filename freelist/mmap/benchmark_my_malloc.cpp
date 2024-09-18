#include "src/allocator.h"
#include <benchmark/benchmark.h>

// Benchmark for custom allocator malloc and free (combined)
static void BM_CustomMalloc(benchmark::State& state) {
    Allocator allocator;
    for (auto _ : state) {
        void* ptr = allocator.my_malloc(state.range(0));
        allocator.my_free(ptr);
    }
}
BENCHMARK(BM_CustomMalloc)->Range(8, 8 << 10);


BENCHMARK_MAIN();

