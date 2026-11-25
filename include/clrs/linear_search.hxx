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
    int32x4_t   v_key = vdupq_n_s32(key);
    std::size_t i     = 0;

    for (; i + 16 <= a.size(); i += 16) {
        int32x4_t  d0 = vld1q_s32(a.data() + i);
        int32x4_t  d1 = vld1q_s32(a.data() + i + 4);
        int32x4_t  d2 = vld1q_s32(a.data() + i + 8);
        int32x4_t  d3 = vld1q_s32(a.data() + i + 12);

        uint32x4_t r0 = vceqq_s32(d0, v_key);
        uint32x4_t r1 = vceqq_s32(d1, v_key);
        uint32x4_t r2 = vceqq_s32(d2, v_key);
        uint32x4_t r3 = vceqq_s32(d3, v_key);

        uint32x4_t result = vorrq_u32(vorrq_u32(r0, r1), vorrq_u32(r2, r3));

        if (vmaxvq_u32(result) != 0) {
            for (std::size_t j = i; j < i + 16; j++)
                if (a[j] == key) return j;
        }
    }

    for (; i + 4 <= a.size(); i += 4) {
        const uint32x4_t m = vceqq_s32(vld1q_s32(a.data() + i), v_key);
        if (vmaxvq_u32(m) != 0) {
            for (std::size_t j = i; j < i + 4; ++j)
                if (a[j] == key) return j;
        }
    }

    for (; i < a.size(); ++i) { // tail: leftover elements, one by one
        if (a[i] == key) return i;
    }
    return a.size();
}
} // namespace clrs
