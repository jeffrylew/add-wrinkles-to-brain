#include <gtest/gtest.h>

#include <vector>

static std::vector<int> rotLeft(std::vector<int> a, int d)
{
    std::vector<int> rotated_vec(a.cbegin() + d, a.cend());
    rotated_vec.reserve(a.size());
    rotated_vec.insert(rotated_vec.end(), a.cbegin(), a.cbegin() + d);
    return rotated_vec;
}

// Test case 0
TEST(RotLeftTest, TestCase0) {
    EXPECT_EQ({5, 1, 2, 3, 4}, rotLeft({1, 2, 3, 4, 5}, 4));
}

// Test case 1
TEST(RotLeftTest, TestCase1) {
    EXPECT_EQ(
        {77, 97, 58, 1, 86, 58, 26, 10, 86, 51,
         41, 73, 89, 7, 10, 1, 59, 58, 84, 77},
        rotLeft({41, 73, 89, 7, 10, 1, 59, 58, 84, 77,
                77, 97, 58, 1, 86, 58, 26, 10, 86, 51}, 10));
}

// Test case 10
TEST(RotLeftTest, TestCase10) {
    EXPECT_EQ(
        {87, 97, 33, 47, 70, 37, 8, 53,
         13, 93, 71, 72, 51, 100, 60},
        rotLeft({33, 47, 70, 37, 8, 53, 13, 93,
                 71, 72, 51, 100, 60, 87, 97}, 13));
}