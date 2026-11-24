#pragma once
#include <cstdint>
#include <span>

namespace clrs {
inline std::size_t linear_search_scalar(std::span<const std::int32_t> a, std::int32_t key) noexcept {
    for (std::size_t i = 0; i < a.size(); i++)
        if (a[i] == key) return i;
    return a.size();
}

inline std::size_t linear_search_neon(std::span<const std::int32_t> a, std::int32_t key) noexcept {
    int64x2_t acc   = vdupq_n_s64(0);   // Initiate 4 lanes with 0 value.
    int64x2_t v_key = vdupq_n_s64(key); // Initiate 4 lanes with key value.
    std::size_t i = 0;

    for (; i + 4 <= a.size(); i += 4) {
        // work on a[i], a[i+1], a[i+2], a[i+3]
        acc               = vpadalq_s32(acc, vld1q_s32(a.data() + i));
        uint32x4_t result = vceqq_s32(acc, key);

        if (vmaxvq_u32(result) != 0) {
            for (std::size_t j = 0; j <= i + 3; i++) {
                if (a[j] == key) return j;
            }
        }
    }

    for (; i < a.size(); ++i) {
        // tail: leftover elements, one by one
        if (a[i] == key) return i;
    }
    return a.size();
}
} // namespace clrs
