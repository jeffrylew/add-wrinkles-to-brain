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

//! @brief Second attempt solution passes all test cases
//! @param[in] queries 2-D array of integers representing <operation, data>
//! @return Vector of 0 and 1 indicating if data was present with frequency
static std::vector<int> freqQuerySecondAttempt(
    std::vector<std::vector<int>> queries)
{
    //! Output vector to hold whether frequencies match given value
    std::vector<int> match_freq {};
    
    //! Map of values and their frequencies
    std::unordered_map<int, int> data_freq {};
    
    //! Map of frequencies and their value counts
    std::unordered_map<int, int> freq_counts {};
    
    for (const auto& query_vec : queries)
    {
        const auto operation = query_vec.front();
        const auto data      = query_vec.back();
        
        switch (operation)
        {
        case 1:
        {
            // Insert if not already present and increment frequency
            const auto prev_freq = data_freq[data];
            ++data_freq[data];
            
            // Update freq_counts, decrementing previous
            // frequency and incrementing new frequency
            if (--freq_counts[prev_freq] < 1)
            {
                // If count for frequency is 0, remove from freq_counts
                freq_counts.erase(prev_freq);
            }
            ++freq_counts[data_freq[data]];
            break;
        }
        case 2:
        {
            auto prev_freq_it = data_freq.find(data);
            if (prev_freq_it != data_freq.end())
            {
                // Save previous frequency
                const auto prev_freq = prev_freq_it->second;
                
                // Decrement previous frequency in freq_counts
                if (--freq_counts[prev_freq] < 1)
                {
                    // If count for frequency is 0, remove from freq_counts
                    freq_counts.erase(prev_freq);
                }
                
                // If data is in data_freq and its frequency is 0,
                // remove from data_freq map
                if (--data_freq[data] < 1)
                {
                    data_freq.erase(data);   
                }
                else
                {
                    ++freq_counts[data_freq[data]];
                }
            }
            break;
        }
        case 3:
            if (freq_counts.count(data) > 0 && freq_counts[data] > 0)
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

} // static std::vector<int> freqQuerySecondAttempt( ...

//! @brief Solution from discussion section
//! @param[in] queries 2-D array of integers representing <operation, data>
//! @return Vector of 0 and 1 indicating if data was present with frequency
static std::vector<int> freqQueryDiscussionSolution(
    std::vector<std::vector<int>> queries)
{
    //! Output vector to hold whether frequencies match given value
    std::vector<int> match_freq {};

    //! first map contains <element, frequency> pairs
    std::unordered_map<int, int> first {};

    //! second map contains <frequency, frequencyCount> pairs
    std::unordered_map<int, int> second {};

    for (std::size_t i = 0; i < queries.size(); ++i)
    {
        const auto& query_vec = queries[i];
        const auto  operation = query_vec.front();
        const auto  data      = query_vec.back();

        if (operation == 1)
        {
            //! Insert data into first map
            //! Update the frequencies in second map
            //! curr_freq = current frequency of data
            int curr_freq = first[data];
            if (curr_freq > 0)
            {
                //! data was already present
                --second[curr_freq];
            }
            
            //! Add data and increase its frequency
            ++first[data];

            //! Update count of new frequency in second map
            ++second[first[data]];
        }
        else if (operation == 2)
        {
            //! Remove data
            if (first.count(data) > 0)
            {
                // data is present, update frequency count
                --second[first[data]];

                // Decrease element frequency
                --first[data];

                // Update frequency count
                ++second[first[data]];
            }
        }
        else
        {
            // Check for the data frequency of any element
            if (second[data] > 0)
            {
                match_freq.emplace_back(1);
            }
            else
            {
                match_freq.emplace_back(0);
            }
        }

    } // for (std::size_t i = 0; i < queries.size(); ++i)
    
    return match_freq;

} // static std::vector<int> freqQueryDiscussionSolution( ...

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
    
    const auto matching_freqs2 = freqQuerySecondAttempt(queries);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           matching_freqs2.cbegin()));

    const auto matching_freqs_DS = freqQueryDiscussionSolution(queries);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           matching_freqs_DS.cbegin()));
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

    const auto matching_freqs2 = freqQuerySecondAttempt(queries);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           matching_freqs2.cbegin()));
    
    const auto matching_freqs_DS = freqQueryDiscussionSolution(queries);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           matching_freqs_DS.cbegin()));
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

    const auto matching_freqs2 = freqQuerySecondAttempt(queries);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           matching_freqs2.cbegin()));
    
    const auto matching_freqs_DS = freqQueryDiscussionSolution(queries);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           matching_freqs_DS.cbegin()));
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
    
    const auto matching_freqs2 = freqQuerySecondAttempt(queries);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           matching_freqs2.cbegin()));
    
    const auto matching_freqs_DS = freqQueryDiscussionSolution(queries);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           matching_freqs_DS.cbegin()));
}