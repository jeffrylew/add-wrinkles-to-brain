#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

//! @brief First attempt solution passes all test cases
//! @param[in] arr Vector of integers
//! @return Strings for positive ratio, negative ratio, and zero ratio
static std::tuple<std::string, std::string, std::string> plusMinus(
    std::vector<int> arr)
{
    int num_negative {};
    int num_zero {};
    int num_positive {};
    
    std::for_each(arr.cbegin(),
                  arr.cend(),
                  [&](int ele) {
                      if (ele < 0)
                      {
                          ++num_negative;
                      }
                      else if (ele == 0)
                      {
                          ++num_zero;
                      }
                      else
                      {
                          ++num_positive;
                      }
                  });
    
    const auto arr_size = static_cast<double>(arr.size());
    
    return std::make_tuple(std::to_string(num_positive / arr_size),
                           std::to_string(num_negative / arr_size),
                           std::to_string(num_zero / arr_size));

} // static std::tuple<std::string, std::string, std::string> plusMinus( ...

// Test case 1
TEST(PlusMinusTest, TestCase1) {
    const std::string positive_ratio {"0.500000"};
    const std::string negative_ratio {"0.333333"};
    const std::string zero_ratio {"0.166667"};

    EXPECT_EQ(std::tie(positive_ratio, negative_ratio, zero_ratio),
              plusMinus({-4, 3, -9, 0, 4, 1}));
}

// Test case 11
TEST(PlusMinusTest, TestCase11) {
    const std::string positive_ratio {"0.375000"};
    const std::string negative_ratio {"0.375000"};
    const std::string zero_ratio {"0.250000"};

    EXPECT_EQ(std::tie(positive_ratio, negative_ratio, zero_ratio),
              plusMinus({1, 2, 3, -1, -2, -3, 0, 0}));
}