#pragma once
#include <cstdint>
#include <span>

namespace clrs {
inline void insertion_sort_scalar(std::span<std::int32_t> a) noexcept {
    for (std::size_t i = 1; i < a.size(); ++i) {
        std::int32_t key = a[i];
        std::size_t j = i;

        while (j > 0 && a[j - 1] > key) {
           a[j] = a[j - 1];
           --j; 
        }
        a[j] = key;
    }
}
} // namespace clrs
