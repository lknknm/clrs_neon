#include <benchmark/benchmark.h>
#include <clrs/sum.hxx>
#include <cstdint>
#include <random>
#include <vector>

static std::vector<std::int32_t> make_input(std::int64_t n) {
    std::mt19937 rng(42);
    std::uniform_int_distribution<std::int32_t> dist;
    std::vector<std::int32_t> v(static_cast<std::size_t>(n));
    for (auto& x : v) x = dist(rng);
    return v;
}

static void BM_SumScalar(benchmark::State& state) {
    auto v = make_input(state.range(0));
    for (auto _ : state) {
        benchmark::DoNotOptimize(v);
        auto r = clrs::sum_scalar(v);
        benchmark::DoNotOptimize(r);
    }
    state.SetItemsProcessed(state.iterations() * state.range(0));
}

static void BM_SumNeon(benchmark::State& state) {
    auto v = make_input(state.range(0));
    for (auto _ : state) {
        benchmark::DoNotOptimize(v);
        auto r = clrs::sum_neon(v);
        benchmark::DoNotOptimize(r);
    }
    state.SetItemsProcessed(state.iterations() * state.range(0));
}

BENCHMARK(BM_SumScalar)->Range(8, 1 << 20);
BENCHMARK(BM_SumNeon)->Range(8, 1 << 20);

BENCHMARK_MAIN();
