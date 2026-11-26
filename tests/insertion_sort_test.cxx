#include <gtest/gtest.h>
#include <clrs/insertion_sort.hxx>
#include <algorithm>
#include <numeric>
#include <vector>
#include <random>
#include <ranges>

class InsertionSortBySize : public ::testing::TestWithParam<std::size_t> {};

TEST_P(InsertionSortBySize, SortsRandomValues) {
    std::mt19937 rng(42);
    std::uniform_int_distribution<std::int32_t> dist;
    std::vector<std::int32_t> v(GetParam());
    for (auto& x : v) x = dist(rng);

    auto expected = v;
    std::ranges::sort(expected);
    clrs::insertion_sort_scalar(v);

    EXPECT_EQ(v, expected);
}

TEST_P(InsertionSortBySize, SortsReversed) {
    std::mt19937 rng(42);
    std::uniform_int_distribution<std::int32_t> dist;
    std::vector<std::int32_t> v(GetParam());
    std::iota(v.begin(), v.end(), 0);
    std::ranges::reverse(v);

    auto expected = v;
    std::ranges::sort(expected);
    clrs::insertion_sort_scalar(v);

    EXPECT_EQ(v, expected);
}

INSTANTIATE_TEST_SUITE_P(Sizes, InsertionSortBySize, ::testing::Range<std::size_t>(0, 65));
