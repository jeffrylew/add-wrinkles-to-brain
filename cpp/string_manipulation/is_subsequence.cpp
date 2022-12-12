#include <gtest/gtest.h>

#include <string>

static bool rec_isSubsequenceDCGreedy(const std::string& source,
                                      const std::string& target,
                                      int                leftIdx,  //
                                      int                rightIdx, //
                                      int                s_size,   //
                                      int                t_size)
{
    //! @details Uses tail recursion. Time complexity O(t_size),
    //!          space complexity O(t_size) without tail recursion optimization

    //! Base cases
    if (leftIdx == s_size)
    {
        return true;
    }
    if (rightIdx == t_size)
    {
        return false;
    }
    
    if (source[leftIdx] == target[rightIdx])
    {
        ++leftIdx;
    }
    ++rightIdx;

    return rec_isSubsequenceDCGreedy(source,   //
                                     target,   //
                                     leftIdx,  //
                                     rightIdx, //
                                     s_size,   //
                                     t_size);

} // static bool rec_isSubsequenceDCGreedy( ...

//! @brief Divide and conquer solution with greedy matching
//! @param[in] s Source string
//! @param[in] t Target string
//! @return True if s is a subsequence of t, else false
static bool isSubsequenceDCGreedy(std::string s, std::string t)
{
    //! @details https://leetcode.com/problems/is-subsequence/solutions/640928/
    //!          official-solution/

    const auto s_size = static_cast<int>(s.size());
    const auto t_size = static_cast<int>(t.size());

    return rec_isSubsequenceDCGreedy(s, t, 0, 0, s_size, t_size);

} // static bool isSubsequenceDCGreedy( ...

//! @brief Two-pointers solution
//! @param[in] s Source string
//! @param[in] t Target string
//! @return True if s is a subsequence of t, else false
static bool isSubsequenceTwoPtrs(std::string s, std::string t)
{
    const auto s_size = static_cast<int>(s.size());
    const auto t_size = static_cast<int>(t.size());

    int s_idx = 0;
    int t_idx = 0;

    while (s_idx < s_size && t_idx < t_size)
    {
        //! Move both pointers or just the t_idx pointer
        if (s[s_idx] == t[t_idx])
        {
            ++s_idx;
        }
        ++t_idx;
    }
    
    return s_idx == s_size;

} // static bool isSubsequenceTwoPtrs( ...

TEST(IsSubsequenceTest, SampleTest)
{
    EXPECT_TRUE(isSubsequenceDCGreedy("abc", "ahbgdc"));
    EXPECT_FALSE(isSubsequenceDCGreedy("axc", "ahbgdc"));

    EXPECT_TRUE(isSubsequenceTwoPtrs("abc", "ahbgdc"));
    EXPECT_FALSE(isSubsequenceTwoPtrs("axc", "ahbgdc"));
}