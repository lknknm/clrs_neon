# linear_search: scalar vs NEON

## Setup
- Machine: Apple M4 - MacMini 2025
- Compiler: Homebrew Clang 22.1.4, `-O3 -std=c++26` (CMake Release)
- Command: `./linear_search \
    --benchmark_repetitions=10 --benchmark_report_aggregates_only=true \
    --benchmark_out=results/linear_search-m4-2026-11-24.json --benchmark_out_format=json`
- Raw data: [results/linear_search-m4-2026-11-24.json](../../results/sum-m1-2026-11-24.json)

## Results:

The following updated results use a 16-wide unroll:

Load 4 vectors (16 × int32), compare each against the broadcast key, OR the 4 masks together in a depth-2 tree, then do a single vmaxvq_u32 + branch per 16 elements. The across-lane reduction and SIMD→GPR transfer are the expensive steps, so the cost is paid once per 16 elements instead of once per 4. Leftovers cascade through a 4-wide loop, then a scalar tail.

Run: 2026-11-26T00:31:25+01:00, 10 CPUs, library build: release

| Size | BM_LinearSearchScalar (G el/s) | BM_LinearSearchNeon (G el/s) | BM_LinearSearchNeon vs BM_LinearSearchScalar |
|---:|---:|---:|---:|
| 8 | 3.02 | 4.70 | 1.56× |
| 64 | 3.31 | 20.03 | 6.05× |
| 512 | 3.28 | 22.42 | 6.83× |
| 4096 | 3.48 | 22.45 | 6.44× |
| 32768 | 3.51 | 22.52 | 6.41× |
| 262144 | 3.53 | 22.44 | 6.36× |
| 1048576 | 3.52 | 22.35 | 6.35× |

---

## Setup
- Machine: Apple M4 - MacMini 2025
- Compiler: Homebrew Clang 22.1.4, `-O3 -std=c++26` (CMake Release)
- Command: `./linear_search \
    --benchmark_repetitions=10 --benchmark_report_aggregates_only=true \
    --benchmark_out=results/linear_search-m4-2026-11-24.json --benchmark_out_format=json`
- Raw data: [results/linear_search-m4-2026-11-24.json](../../results/sum-m1-2026-11-24.json)

## Results (median of 10)
Run: 2026-11-25T17:13:10+01:00, 10 CPUs, library build: release

| Size | BM_LinearSearchScalar (G el/s) | BM_LinearSearchNeon (G el/s) | BM_LinearSearchNeon vs BM_LinearSearchScalar |
|---:|---:|---:|---:|
| 8 | 3.02 | 5.65 | 1.87× |
| 64 | 3.31 | 10.52 | 3.18× |
| 512 | 3.27 | 10.40 | 3.18× |
| 4096 | 3.48 | 12.19 | 3.50× |
| 32768 | 3.50 | 12.67 | 3.62× |
| 262144 | 3.51 | 12.74 | 3.63× |
| 1048576 | 3.52 | 12.73 | 3.62× |

## Observations
- The scalar version is flat at about 3.5 G el/s at every size. At the roughly 4.4GHz Apple M4, this represents about one element per cycle, potentially meaning Clang did not vectorise the scalar early-exit loop, comparing one element at a time.

Considering:
> cycles per element = clock (GHz) ÷ throughput (G el/s)

The M4's performance cores run at roughly 4.4 GHz. Scalar search: 4.4 ÷ 3.5 ≈ 1.3 cycles per element. NEON: 4.4 ÷ 12.7 ≈ 0.35 cycles per element, or about 1.4 cycles per group of 4.

- NEON reaches ~12.7G el/s (~1.4 cycles per group of 4), 3.6x faster from 4096 up.
- Smaller sizes have a smaller gain as only 2 vector groups run.
- TODO: unroll to 16 elements so the reduction + branch is paid once per 16 el.
