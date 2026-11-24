#pragma once
#include <cstdint>
#include <span>
#include <arm_neon.h>

namespace clrs {
inline std::size_t linear_search_scalar(std::span<const std::int32_t> a, std::int32_t key) noexcept {
    for (std::size_t i = 0; i < a.size(); i++)
        if (a[i] == key) return i;
    return a.size();
}

/*
 * Linear search (CLRS §2.1, exercise), AArch64 NEON version.
 *
 * Returns the index of the first element equal to `key`, or a.size() if absent.
 *
 * Scheme, 4 x int32 lanes per 128-bit register:
 *
 *   v_key  = [ key | key | key | key ]        vdupq_n_s32   (once, before loop)
 *
 *   for each group of 4 elements a[i..i+3]:
 *     data = [ a0  | a1  | a2  | a3  ]        vld1q_s32
 *     mask = [ m0  | m1  | m2  | m3  ]        vceqq_s32     (lane = 0xFFFFFFFF on match, 0 otherwise)
 *     any  = max(m0, m1, m2, m3)              vmaxvq_u32    (nonzero => match in this group)
 *     if any: scalar scan a[i..i+3]           returns the first matching index
 *
 *   tail (a.size() % 4 elements): scalar loop.
 *
 * Cost: one compare + one across-lane reduction + one branch per 4 elements.
 * TODO: unroll to 16 elements, OR the 4 masks, reduce and branch once.
 */
inline std::size_t linear_search_neon(std::span<const std::int32_t> a, std::int32_t key) noexcept {
    int32x4_t v_key = vdupq_n_s32(key); // Initiate 4 lanes with key value.
    std::size_t i   = 0;

    for (; i + 4 <= a.size(); i += 4) {
        // work on a[i], a[i+1], a[i+2], a[i+3]
        int32x4_t  data   = vld1q_s32(a.data() + i);
        uint32x4_t result = vceqq_s32(data, v_key);

        if (vmaxvq_u32(result) != 0) {
            for (std::size_t j = i; j <= i + 3; j++)
                if (a[j] == key) return j;
        }
    }
    for (; i < a.size(); ++i) { // tail: leftover elements, one by one
        if (a[i] == key) return i;
    }
    return a.size();
}
} // namespace clrs
