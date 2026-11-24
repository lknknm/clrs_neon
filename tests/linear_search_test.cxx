#include <gtest/gtest.h>
#include <clrs/linear_search.hxx>
#include <algorithm>
#include <numeric>
#include <vector>

class LinearSearchBySize : public ::testing::TestWithParam<std::size_t> {};

// Distinct values 0..n-1, then search for every one of them.
TEST_P(LinearSearchBySize, FindsKeyAtEveryPosition) {
    const std::size_t n = GetParam();
    std::vector<std::int32_t> v(n);
    std::iota(v.begin(), v.end(), 0);

    for (std::size_t pos = 0; pos < n; ++pos) {
        const auto key      = static_cast<std::int32_t>(pos);
        const auto expected = static_cast<std::size_t>(std::ranges::find(v, key) - v.begin());
        EXPECT_EQ(clrs::linear_search_scalar(v, key), expected) << "pos=" << pos;
        EXPECT_EQ(clrs::linear_search_neon(v, key), expected) << "pos=" << pos;
    }
}

TEST_P(LinearSearchBySize, AbsentKeyReturnsSize) {
    const std::size_t n = GetParam();
    std::vector<std::int32_t> v(n, 0);
    EXPECT_EQ(clrs::linear_search_scalar(v, 1), n);
    EXPECT_EQ(clrs::linear_search_neon(v, 1), n);
}

INSTANTIATE_TEST_SUITE_P(Sizes, LinearSearchBySize, ::testing::Range<std::size_t>(0, 65));
