#include <gtest/gtest.h>
#include <clrs/sum.hxx>
#include <numeric>
#include <vector>

TEST(Sum, MatchesStdReduce) {
    std::vector<std::int32_t> v = {1, 2, 3, 4, 5};
    EXPECT_EQ(clrs::sum_scalar(v), std::reduce(v.begin(), v.end(), std::int64_t{0}));
}
