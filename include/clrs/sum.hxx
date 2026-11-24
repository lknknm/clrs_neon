#pragma once
#include <cstdint>
#include <span>

#include <arm_neon.h>

namespace clrs {
inline std::int64_t sum_scalar(std::span<const std::int32_t> a) noexcept {
    std::int64_t total = 0;
    for (std::int32_t x : a) total += x;
    return total;
}

inline std::int64_t sum_neon(std::span<const std::int32_t> a) noexcept {
    int64x2_t acc = vdupq_n_s64(0); // 4 lanes, all zero
    std::size_t i = 0;
    for (; i + 4 <= a.size(); i += 4)
        acc = vpadalq_s32(acc, vld1q_s32(a.data() + i));
    
    std::int64_t total = vaddvq_s64(acc);    // add the 4 lanes, widened to 64 bits
    for (; i < a.size(); i++) total += a[i]; // tail: 0-3 leftover elements
    return total;
}
} // namespace clrs
