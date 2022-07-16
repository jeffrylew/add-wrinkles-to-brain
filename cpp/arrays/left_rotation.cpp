#include <gtest/gtest.h>

#include <algorithm>
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
    std::vector<int> expected_vec {5, 1, 2, 3, 4};
    const auto       rotated_vec = rotLeft({1, 2, 3, 4, 5}, 4);

    EXPECT_TRUE(std::equal(expected_vec.cbegin(),
                           expected_vec.cend(),
                           rotated_vec.cbegin()));
}

// Test case 1
TEST(RotLeftTest, TestCase1) {
    std::vector<int> expected_vec {77, 97, 58, 1, 86, 58, 26, 10, 86, 51,
                                   41, 73, 89, 7, 10, 1, 59, 58, 84, 77};

    const auto rotated_vec =
        rotLeft({41, 73, 89, 7, 10, 1, 59, 58, 84, 77,
                 77, 97, 58, 1, 86, 58, 26, 10, 86, 51}, 10);

    EXPECT_TRUE(std::equal(expected_vec.cbegin(),
                           expected_vec.cend(),
                           rotated_vec.cbegin()));
}

// Test case 10
TEST(RotLeftTest, TestCase10) {
    std::vector<int> expected_vec {87, 97, 33, 47, 70, 37, 8, 53,
                                   13, 93, 71, 72, 51, 100, 60};

    const auto rotated_vec = rotLeft({33, 47, 70, 37, 8, 53, 13, 93,
                                      71, 72, 51, 100, 60, 87, 97}, 13);

    EXPECT_TRUE(std::equal(expected_vec.cbegin(),
                           expected_vec.cend(),
                           rotated_vec.cbegin()));
}