#pragma once
#include <cstdint>
#include <span>

namespace clrs {
inline std::int64_t sum_scalar(std::span<const std::int32_t> a) noexcept {
    std::int64_t total = 0;
    for (std::int32_t x : a) total += x;
    return total;
}
}
