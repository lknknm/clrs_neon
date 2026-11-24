#include <gtest/gtest.h>
#include <clrs/sum.hxx>
#include <numeric>
#include <random>
#include <vector>

class SumBySize : public ::testing::TestWithParam<std::size_t> {};

TEST_P(SumBySize, MatchesStdReduce) {
    std::mt19937 rng(42);                             // fixed seed.
    std::uniform_int_distribution<std::int32_t> dist; // full int32 range.
    std::vector<std::int32_t> v(GetParam()); 
    for (auto& x : v) x = dist(rng);

    EXPECT_EQ(clrs::sum_scalar(v), std::reduce(v.begin(), v.end(), std::int64_t{0}, std::plus<std::int64_t>{}));
}

INSTANTIATE_TEST_SUITE_P(Sizes, SumBySize, ::testing::Range<std::size_t>(0, 65));
