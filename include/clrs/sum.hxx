#pragma once
#include <cstdint>
#include <span>

#include <arm_neon.h>

namespace clrs {
inline std::int64_t sum_scalar(std::span<const std::int32_t> a) noexcept {
  std::int64_t total = 0;
  for (std::int32_t x : a)
    total += x;
  return total;
}

/*
 * Sum all elements of an array. AArch64 NEON version.
 *
 * Returns the total sum for all the values in an array.
 *
 * Scheme: elements loaded as 4 x int32, accumulated as 2 x int64.
 *
 *   acc = [   0   |   0   ]             vdupq_n_s64     (2 x int64)
 *
 *   for each group of 4 elements a[i...i+3]
 *       data = [ a0 | a1 | a2 | a3 ]    vld1q_s32       (4 x int32)
 *       acc += [ a0 + a1 | a2 + a3 ]    vpadalq_s32     (pairs widened to
 * int64, then added)
 *
 *   total = acc[0] + acc[1]             vaddvq_s64
 *
 *   tail (a.size() % 4 elements): scalar loop, added to total
 */
inline std::int64_t sum_neon(std::span<const std::int32_t> a) noexcept {
  int64x2_t acc0 = vdupq_n_s64(0);
  int64x2_t acc1 = vdupq_n_s64(0);
  int64x2_t acc2 = vdupq_n_s64(0);
  int64x2_t acc3 = vdupq_n_s64(0);
  std::size_t i = 0;

  for (; i + 16 <= a.size(); i += 16) {
    acc0 = vpadalq_s32(acc0, vld1q_s32(a.data() + i));
    acc1 = vpadalq_s32(acc1, vld1q_s32(a.data() + i + 4));
    acc2 = vpadalq_s32(acc2, vld1q_s32(a.data() + i + 8));
    acc3 = vpadalq_s32(acc3, vld1q_s32(a.data() + i + 12));
  }

  int64x2_t acc = vaddq_s64(vaddq_s64(acc0, acc1), vaddq_s64(acc2, acc3));
  std::int64_t total = vaddvq_s64(acc);

  for (; i < a.size(); i++)
    total += a[i]; // tail: 0-3 leftover elements
  return total;
}
} // namespace clrs
