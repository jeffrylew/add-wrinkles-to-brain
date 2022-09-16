#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

static std::vector<int> compareTriplets(std::vector<int> a, std::vector<int> b)
{
    std::vector<int> alice_bob(2ULL);
    
    for (std::size_t i= 0; i < a.size(); ++i)
    {
        if (a[i] > b[i])
        {
            ++alice_bob.front();
        }
        else if (a[i] < b[i])
        {
            ++alice_bob.back();
        }
    }
    
    return alice_bob;

} // static std::vector<int> compareTriplets( ...

// Test case 0
TEST(CompareTripletsTest, TestCase0) {
    const std::vector<int> expected_result {1, 1};

    const auto alice_bob = compareTriplets({5, 6, 7}, {3, 6, 10});

    EXPECT_TRUE(std::equal(expected_result.cbegin(),
                           expected_result.cend(),
                           alice_bob.cbegin()));
}

// Test case 7
TEST(CompareTripletsTest, TestCase7) {
    const std::vector<int> expected_result {2, 1};

    const auto alice_bob = compareTriplets({17, 28, 30}, {99, 16, 8});

    EXPECT_TRUE(std::equal(expected_result.cbegin(),
                           expected_result.cend(),
                           alice_bob.cbegin()));
}