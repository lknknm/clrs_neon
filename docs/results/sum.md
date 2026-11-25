# sum: scalar vs NEON

## Setup
- Machine: Apple M4 - MacMini 2025
- Compiler: Homebrew Clang 22.1.4, `-O3 -std=c++26` (CMake Release)
- Command: `sum_bench \
    --benchmark_repetitions=10 --benchmark_report_aggregates_only=true \
    --benchmark_out=results/sum-m1-2026-11-24.json --benchmark_out_format=json`
- Raw data: [results/sum-m1-2026-11-24.json](../../results/sum-m1-2026-11-24.json)

## Results (median of 10)
Run: 2026-11-25T16:22:14+01:00, 10 CPUs, library build: release

| Size | BM_SumScalar (G el/s) | BM_SumNeon (G el/s) | BM_SumNeon vs BM_SumScalar |
|---:|---:|---:|---:|
| 8 | 5.63 | 4.73 | 0.84× |
| 64 | 27.59 | 31.06 | 1.13× |
| 512 | 23.89 | 36.79 | 1.54× |
| 4096 | 18.25 | 25.23 | 1.38× |
| 32768 | 17.53 | 22.89 | 1.31× |
| 262144 | 16.99 | 21.98 | 1.29× |
| 1048576 | 16.82 | 21.83 | 1.30× |

## Observations
- NEON wins from 64 elements up, peaking at 1.54× around 512 (L1-resident).
