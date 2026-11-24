# clrs-neon

Ports of algorithms from *Introduction to Algorithms* (CLRS) [1] to ARM NEON SIMD, written in C++26 and tested with GoogleTest.

Not every algorithm in the book suits SIMD. This repository covers the ones that do and tests each NEON port.

The algorithm implementations are in the `include` folder, under `include/clrs/`.

## How to build

Both platforms need CMake ≥ 3.24 and Clang with C++26 support.

### macOS (Apple Silicon)

The binaries run natively, so this is the setup to use for benchmarking.

```sh
cmake --preset clang-release
cmake --build build/clang-release
ctest --test-dir build/clang-release --output-on-failure
```

Run the benchmarks:

```sh
./build/clang-release/sum_bench
```

### Linux (cross-compiled, run with QEMU)

Additional requirements:

- An AArch64 GNU sysroot at `/usr/aarch64-linux-gnu`
- `qemu-aarch64` (user-mode emulation)

```sh
cmake --preset clang-aarch64
cmake --build build/clang-aarch64
ctest --test-dir build/clang-aarch64 --output-on-failure
```

Run the benchmarks:

```sh
qemu-aarch64 -L /usr/aarch64-linux-gnu ./build/clang-aarch64/sum_bench --benchmark_min_time=0.01s
```

> [!WARNING]
> We don't recommend benchmarking under QEMU. The emulator translates NEON instructions on-the-fly instead of running them on hardware, so the timings do not reflect real performance. NEON results can even come out slower than scalar. Use this setup to check correctness, and benchmark on real ARM hardware.

## References

[1] T. H. Cormen, C. E. Leiserson, R. L. Rivest, and C. Stein, *Introduction to Algorithms*, 4th ed. Cambridge, MA, USA: MIT Press, 2022.

[2] Arm Ltd., "Neon Programmer's Guide for Armv8-A," Arm Developer Documentation, doc. 102159. [Online]. Available: https://developer.arm.com/documentation/102159/latest
