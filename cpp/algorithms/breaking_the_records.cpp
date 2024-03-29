#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Find number of times least and most points records were broken
//! @param[in] scores Vector of points scored per game
//! @return Vector with most points records in index 0 and least in index 1
static std::vector<int> breakingRecords(std::vector<int> scores)
{
    std::vector<int> output(2ULL);
    
    int min {scores.front()};
    int max {scores.front()};
    
    for (const int score : scores)
    {
        if (score < min)
        {
            min = score;
            ++output[1];
        }
        else if (score > max)
        {
            max = score;
            ++output[0];
        }
    }
    
    return output;

} // static std::vector<int> breakingRecords( ...

//! @brief Solution from HR discussion section
//! @param[in] scores Vector of points scored per game
//! @return Vector with most points records in index 0 and least in index 1
static std::vector<int> breakingRecordsDS(std::vector<int> scores)
{
    //! @details https://www.hackerrank.com/challenges/
    //!          breaking-best-and-worst-records/forum

    int min {scores[0]};
    int max {scores[0]};

    int minCount {};
    int maxCount {};
    
    for (const int score : scores)
    {
        if (score < min)
        {
            min = score;
            ++minCount;
        }
        else if (score > max)
        {
            max = score;
            ++maxCount;
        }
    }
    
    return {maxCount, minCount};

} // static std::vector<int> breakingRecordsDS( ...

// Test case 0
TEST(BreakingRecordsTest, TestCase0)
{
    const std::vector<int> expected_output {2, 4};

    const auto result = breakingRecords({10, 5, 20, 20, 4, 5, 2, 25, 1});

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));
    
    const auto resultDS = breakingRecordsDS({10, 5, 20, 20, 4, 5, 2, 25, 1});

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           resultDS.cbegin()));
}

// Test case 1
TEST(BreakingRecordsTest, TestCase1)
{
    const std::vector<int> expected_output {4, 0};

    const auto result = breakingRecords({3, 4, 21, 36, 10, 28, 35, 5, 24, 42});

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));
    
    const auto resultDS =
        breakingRecordsDS({3, 4, 21, 36, 10, 28, 35, 5, 24, 42});

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           resultDS.cbegin()));
}