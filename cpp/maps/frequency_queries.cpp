#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <vector>

//! @brief First attempt solution times out for Test case 11
//! @param[in] queries 2-D array of integers representing <operation, data>
//! @return Vector of 0 and 1 indicating if data was present with frequency
static std::vector<int> freqQueryFirstAttempt(
    std::vector<std::vector<int>> queries)
{
    //! Output vector to hold whether frequencies match given value
    std::vector<int> match_freq {};
    
    //! Map of values and their frequencies
    std::unordered_map<int, int> data_freq {};
    
    for (const auto& query_vec : queries)
    {
        const auto operation = query_vec.front();
        const auto data      = query_vec.back();
        
        switch (operation)
        {
        case 1:
            //! Insert if not already present and increment frequency
            ++data_freq[data];
            break;
        case 2:
            if (data_freq.count(data) > 0 && --data_freq[data] == 0)
            {
                //! If data is in map and its frequency is 0, remove from map
                data_freq.erase(data);
            }
            break;
        case 3:
            if (std::any_of(data_freq.cbegin(),
                            data_freq.cend(),
                            [data](decltype(data_freq)::const_reference kv) -> bool {
                                return kv.second == data;
                            }))
            {
                match_freq.emplace_back(1);
            }
            else
            {
                match_freq.emplace_back(0);
            }
            break;
        }
        
    } // for (const auto& query_vec : ...
    
    return match_freq;

} // static std::vector<int> freqQueryFirstAttempt( ...

// Try sample inputs given in problem description
TEST(FreqQueryTest, SampleInputs) {
    const std::vector<std::vector<int>> queries {
        {1, 1},
        {2, 2},
        {3, 2},
        {1, 1},
        {1, 1},
        {2, 1},
        {3, 2}};

    const std::vector<int> expected_output {0, 1};

    const auto matching_freqs = freqQueryFirstAttempt(queries);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           matching_freqs.cbegin()));
}

// Test case 0
TEST(FreqQueryTest, TestCase0) {
    const std::vector<std::vector<int>> queries {
        {1, 5},
        {1, 6},
        {3, 2},
        {1, 10},
        {1, 10},
        {1, 6},
        {2, 5},
        {3, 2}};

    const std::vector<int> expected_output {0, 1};

    const auto matching_freqs = freqQueryFirstAttempt(queries);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           matching_freqs.cbegin()));
}

// Test case 1
TEST(FreqQueryTest, TestCase1) {
    const std::vector<std::vector<int>> queries {
        {3, 4},
        {2, 1003},
        {1, 16},
        {3, 1}};

    const std::vector<int> expected_output {0, 1};

    const auto matching_freqs = freqQueryFirstAttempt(queries);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           matching_freqs.cbegin()));
}

// Test case 2
TEST(FreqQueryTest, TestCase2) {
    const std::vector<std::vector<int>> queries {
        {1, 3},
        {2, 3},
        {3, 2},
        {1, 4},
        {1, 5},
        {1, 5},
        {1, 4},
        {3, 2},
        {2, 4},
        {3, 2}};

    const std::vector<int> expected_output {0, 1, 1};

    const auto matching_freqs = freqQueryFirstAttempt(queries);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           matching_freqs.cbegin()));
}