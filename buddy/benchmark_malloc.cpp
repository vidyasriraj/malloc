
#include <benchmark/benchmark.h>
#include <cstdlib>  // For malloc and free

// Benchmark for system malloc and free (combined)
static void BM_SystemMalloc(benchmark::State& state) {
    for (auto _ : state) {
        void* ptr = malloc(state.range(0));
        free(ptr);
    }
}
BENCHMARK(BM_SystemMalloc)->Range(8, 8 << 10);




BENCHMARK_MAIN();

