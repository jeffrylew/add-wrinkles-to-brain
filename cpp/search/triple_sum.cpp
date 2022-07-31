#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief First attempt solution times out for Test cases 2, 3, 4, 7, 8
static long tripletsFirstAttempt(std::vector<int> a,
                                 std::vector<int> b,
                                 std::vector<int> c)
{
    // Total number of distinct triplets
    long n_triplets {};
    
    // Sort vectors before removing duplicates and resizing
    // See https://stackoverflow.com/questions/1041620/
    // whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    std::sort(c.begin(), c.end());
    
    // Check case when no triplets can be made
    if (a.front() > b.back() || b.back() < c.front())
    {
        return n_triplets;
    }
    
    auto a_new_end = std::unique(a.begin(), a.end());
    auto b_new_end = std::unique(b.begin(), b.end());
    auto c_new_end = std::unique(c.begin(), c.end());
    
    a.erase(a_new_end, a.end());
    b.erase(b_new_end, b.end());
    c.erase(c_new_end, c.end());

    // Get iterator to first value of b >= first a element
    auto b_init_val_it = std::find_if(b.cbegin(),
                                      b.cend(),
                                      [&](int b_val) -> bool {
                                          return b_val >= a.front();
                                      });
    
    // Loop over values in a
    for (std::size_t i = 0; i < a.size(); ++i)
    {
        // Get iterator to first element in b >= current a element
        auto b_val_it = std::find_if(b_init_val_it,
                                     b.cend(),
                                     [&](int b_val) -> bool {
                                         return b_val >= a.at(i);
                                     });
        
        // For a fixed a value, iterate values of b
        while (b_val_it != b.cend())
        {
            // Increment n_triplets for values of c <= current b_val_it
            n_triplets += std::count_if(c.cbegin(),
                                        c.cend(),
                                        [&](int c_val) -> bool {
                                            return *b_val_it >= c_val;
                                        });
            
            ++b_val_it;
            
        } // while (b_val_it != b.cend())

    } // for (std::size_t i = 0; ...
    
    return n_triplets;

} // static long tripletsFirstAttempt( ...

// Try sample input given in problem description
TEST(TripletsTest, SampleInput) {
    EXPECT_EQ(4L, tripletsFirstAttempt({3, 5, 7}, {3, 6}, {4, 6, 9}));
}

// Test case 0
TEST(TripletsTest, TestCase0) {
    EXPECT_EQ(8L, tripletsFirstAttempt({1, 3, 5}, {2, 3}, {1, 2, 3}));
}

// Test case 1
TEST(TripletsTest, TestCase1) {
    EXPECT_EQ(5L, tripletsFirstAttempt({1, 4, 5}, {2, 3, 3}, {1, 2, 3}));
}

// Test case 9
TEST(TripletsTest, TestCase9) {
    EXPECT_EQ(12L, tripletsFirstAttempt({1, 3, 5, 7},
                                        {5, 7, 9},
                                        {7, 9, 11, 13}));
}