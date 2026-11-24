#include <benchmark/benchmark.h>
#include <clrs/linear_search.hxx>
#include <cstdint>
#include <random>
#include <vector>

static std::vector<std::int32_t> make_input(std::int64_t n) {
    return std::vector<std::int32_t>(static_cast<std::size_t>(n), 0);
}

static void BM_LinearSearchScalar(benchmark::State& state) {
    auto v = make_input(state.range(0));
    std::int32_t key = 1; // guaranteed to exercise full lookup

    for (auto _ : state) {
        benchmark::DoNotOptimize(v);
        auto r = clrs::linear_search_scalar(v, key);
        benchmark::DoNotOptimize(r);
    }
    state.SetItemsProcessed(state.iterations() * state.range(0));
}

static void BM_LinearSearchNeon(benchmark::State& state) {
    auto v = make_input(state.range(0));
    std::int32_t key = 1; // guaranteed to exercise full lookup

    for (auto _ : state) {
        benchmark::DoNotOptimize(v);
        auto r = clrs::linear_search_neon(v, key);
        benchmark::DoNotOptimize(r);
    }
    state.SetItemsProcessed(state.iterations() * state.range(0));
}

BENCHMARK(BM_LinearSearchScalar)->Range(8, 1 << 20);
BENCHMARK(BM_LinearSearchNeon)->Range(8, 1 << 20);

BENCHMARK_MAIN();
