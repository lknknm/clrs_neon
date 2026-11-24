set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_COMPILER_TARGET aarch64-linux-gnu)

# Run AArch64 binaries (tests, gtest discovery) through qemu
set(CMAKE_CROSSCOMPILING_EMULATOR qemu-aarch64 -L /usr/aarch64-linux-gnu)
