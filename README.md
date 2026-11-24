# clrs-neon

Ports of algorithms from *Introduction to Algorithms* (CLRS) [1] to ARM NEON SIMD, written in C++26 and tested with GoogleTest.

Not every algorithm in the book suits SIMD. This repository covers the ones that do and tests each NEON port.

## How to build

Requirements:

- CMake ≥ 3.24
- Clang with C++23 support
- An AArch64 GNU sysroot at `/usr/aarch64-linux-gnu`
- `qemu-aarch64` (user-mode emulation, used to run the tests on non-ARM hosts)

Configure, build, and run the tests:

```sh
cmake --preset clang-aarch64
cmake --build build/clang-aarch64
ctest --test-dir build/clang-aarch64 --output-on-failure
```

## References

[1] T. H. Cormen, C. E. Leiserson, R. L. Rivest, and C. Stein, *Introduction to Algorithms*, 4th ed. Cambridge, MA, USA: MIT Press, 2022.
