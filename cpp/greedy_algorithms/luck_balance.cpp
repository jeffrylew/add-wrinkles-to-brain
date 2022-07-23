#include <gtest/gtest.h>

#include <algorithm>
#include <tuple>
#include <vector>

static int luckBalance(int k, std::vector<std::vector<int>> contests)
{
    // Maximum luck balance achievable
    int max_luck {};
    
    // Store luck associated with important contests
    std::vector<int> luck_ic {};
    
    // Rolling sum of luck in luck_ic
    // Assume Lena must win all contests in luck_ic so sum is negative
    int luck_ic_win_sum {};
    
    for (const auto& lt_vec : contests)
    {
        // l_i is amount of luck associated with contest i
        // t_i is contest i's importance 
        const auto l_i = lt_vec.front();
        const auto t_i = lt_vec.back();
        
        if (0 == t_i)
        {
            // Add luck from unimportant contest
            max_luck += l_i;
        }
        else
        {
            luck_ic.emplace_back(l_i);
            luck_ic_win_sum -= l_i;
        }
        
    } // for (const auto& lt_vec : contests)
    
    // If Lena can lose at least one contest then apply enclosed logic
    if (0 != k)
    {
        // Use the min between k and luck_ic.size() to ensure valid accesses
        // Test cases 6, 7, and 8 segfaulted without this
        const auto max_losses = std::min(k, static_cast<int>(luck_ic.size()));
        
        // Only need to partially sort (descending) luck_ic by max_losses values
        // These max_losses largest elements are the contests Lena should lose
        // to maximize her luck (they add to her score)
        std::partial_sort(luck_ic.begin(),
                          luck_ic.begin() + max_losses,
                          luck_ic.end(),
                          std::greater<int> {});
        
        for (std::size_t i = 0; i < max_losses; ++i)
        {
            max_luck += luck_ic.at(i);
            luck_ic_win_sum += luck_ic.at(i);
        }
    
    } // if (0 != k)
    
    return max_luck + luck_ic_win_sum;

} // static int luckBalance( ...

//! @brief Solution from discussion section
//! @param[in] k        Number of important contests that can be lost
//! @param[in] contests Vector of [L_i, T_i] vectors (luck and importance)
//! @return Maximum amount of luck as an int
static int luckBalanceDiscussionSolution(int k,
                                         std::vector<std::vector<int>> contests)
{
    // Sort from greatest luck to least luck
    std::sort(contests.begin(),
              contests.end(),
              [](const std::vector<int>& lhs,
                 const std::vector<int>& rhs) -> bool {
                  return std::tie(lhs.front(), lhs.back())
                      > std::tie(rhs.front(), rhs.back());
              });
    
    // Maximum luck balance achievable
    int max_luck {};

    for (const auto& lt_vec : contests)
    {
        if (0 == lt_vec.back())
        {
            max_luck += lt_vec.front();
        }
        else if (k > 0)
        {
            max_luck += lt_vec.front();
            --k;
        }
        else
        {
            max_luck -= lt_vec.front();
        }
    }

    return max_luck;

} // static int luckBalanceDiscussionSolution( ...

// Try sample input given in problem description
TEST(LuckBalanceTest, SampleInput) {
    EXPECT_EQ(10,
              luckBalance(2, {{5, 1},
                              {1, 1},
                              {4, 0}}));
    
    EXPECT_EQ(10,
              luckBalanceDiscussionSolution(2, {{5, 1},
                                                {1, 1},
                                                {4, 0}}));
}

// Test case 0
TEST(LuckBalanceTest, TestCase0) {
    EXPECT_EQ(29,
              luckBalance(3, {{5, 1},
                              {2, 1},
                              {1, 1},
                              {8, 1},
                              {10, 0},
                              {5, 0}}));

    EXPECT_EQ(29,
              luckBalanceDiscussionSolution(3, {{5, 1},
                                                {2, 1},
                                                {1, 1},
                                                {8, 1},
                                                {10, 0},
                                                {5, 0}}));
}

// Test case 3
TEST(LuckBalanceTest, TestCase3) {
    EXPECT_EQ(42,
              luckBalance(5, {{13, 1},
                              {10, 1},
                              {9, 1},
                              {8, 1},
                              {13, 1},
                              {12, 1},
                              {18, 1},
                              {13, 1}}));

    EXPECT_EQ(42,
              luckBalanceDiscussionSolution(5, {{13, 1},
                                                {10, 1},
                                                {9, 1},
                                                {8, 1},
                                                {13, 1},
                                                {12, 1},
                                                {18, 1},
                                                {13, 1}}));
}

// Test case 12
TEST(LuckBalanceTest, TestCase12) {
    EXPECT_EQ(21,
              luckBalance(2, {{5, 1},
                              {4, 0},
                              {6, 1},
                              {2, 1},
                              {8, 0}}));

    EXPECT_EQ(21,
              luckBalanceDiscussionSolution(2, {{5, 1},
                                                {4, 0},
                                                {6, 1},
                                                {2, 1},
                                                {8, 0}}));
}

// Test case 6, segfaulted on initial solution
TEST(LuckBalanceTest, TestCase6) {
    const std::vector<std::vector<int>> contests {
        {5351, 0},
        {1870, 0},
        {9359, 0},
        {6828, 0},
        {9896, 0},
        {6335, 0},
        {38, 0},
        {2440, 0},
        {4627, 0},
        {2663, 0},
        {6300, 0},
        {107, 0},
        {4605, 0},
        {5437, 0},
        {4394, 0},
        {7530, 0},
        {8254, 0},
        {5668, 0},
        {6945, 0},
        {1539, 0},
        {1323, 0},
        {1841, 0},
        {2191, 0},
        {8943, 0},
        {7645, 0},
        {3903, 0},
        {4772, 0},
        {2392, 0},
        {1539, 0},
        {7712, 0},
        {9955, 0},
        {9895, 0},
        {7422, 0},
        {4665, 0},
        {5448, 0},
        {2317, 0},
        {6963, 0},
        {9170, 0},
        {2860, 0},
        {3812, 0},
        {5725, 0},
        {1324, 0},
        {7377, 0},
        {5538, 0},
        {2383, 0},
        {7674, 0},
        {5142, 0},
        {3932, 0},
        {2624, 0},
        {8704, 0},
        {5706, 0},
        {2649, 0},
        {6730, 0},
        {8757, 0},
        {2930, 0},
        {4465, 0},
        {6119, 0},
        {4967, 0},
        {8717, 0},
        {334, 0},
        {9962, 0},
        {293, 0},
        {1943, 0},
        {8146, 0},
        {4085, 0},
        {779, 0},
        {9630, 0},
        {1843, 0},
        {289, 0},
        {2083, 0},
        {9742, 0},
        {5891, 0},
        {2996, 0},
        {7447, 0},
        {4371, 0},
        {1102, 0},
        {6501, 0},
        {492, 0},
        {3806, 0},
        {3549, 0},
        {9719, 0},
        {9913, 0},
        {9265, 0},
        {8468, 0},
        {5007, 0},
        {1479, 0},
        {2758, 0},
        {1727, 0},
        {5548, 0},
        {6869, 0},
        {154, 0},
        {42, 0},
        {6309, 0},
        {9041, 0},
        {3036, 0},
        {3282, 0},
        {4828, 0},
        {7036, 0},
        {8724, 0}};

    EXPECT_EQ(494906, luckBalance(99, contests));

    EXPECT_EQ(494906, luckBalanceDiscussionSolution(99, contests));

} // TEST(LuckBalanceTest, TestCase6) { ...