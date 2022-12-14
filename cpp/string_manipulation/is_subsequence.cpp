#include <gtest/gtest.h>

#include <string>
#include <unordered_map>
#include <vector>

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
    //! @details Time complexity O(t_size), space complexity O(1)

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

//! @brief Greedy Matching with Character Indices Hashmap
//! @param[in] s Source string
//! @param[in] t Target string
//! @return True if s is a subsequence of t, else false
static bool isSubsequenceGreedyHashmap(std::string s, std::string t)
{
    //! @details Addresses follow-up question: If there are lots of incoming S,
    //!          say S1, S2, ... and you want to check one by one to see if T
    //!          has its subsequence. In this scenario, how would you change
    //!          your code?
    //!
    //!          Time complexity O(t_size + s_size * log(t_size))
    //!          - Building hashmap out of target string would take O(t_size),
    //!            could redesign API by putting hashmap construction in class
    //!            constructor
    //!          - Scanning through source string is O(s_size). Hashmap lookup
    //!            is constant but finding suitable target index for source
    //!            string would take O(t_size) with linear search or
    //!            O(log(t_size)) with binary search. So this portion of
    //!            algorithm is bounded by O(s_size * log(t_size)). This also
    //!            depends on target string character distribution - if they are
    //!            distributed evenly, hashmap entries would have a shorter list
    //!            of indices and hence a shorter search time. In general, this
    //!            hashmap approach should be faster than the two-pointers
    //!            approach even though their time complexities say otherwise.
    //!          Space complexity O(t_size) for the hashmap consisting of
    //!          indices for each character in target string. In the worst case,
    //!          may have as many keys as values, i.e. eah character corresponds
    //!          to a unique index

    //! Precomputation, build hashmap from target string
    std::unordered_map<char, std::vector<int>> letterIndicesTable {};
    for (int i = 0; i < t.size(); ++i)
    {
        auto ret = letterIndicesTable.emplace(t[i], std::vector<int>({i}));
        if (not ret.second)
        {
            ret.first->second.emplace_back(i);
        }
    }
    
    int currMatchIndex {-1};
    for (const auto letter : s)
    {
        if (letterIndicesTable.count(letter) == 0U)
        {
            return false; // No match, early exit
        }

        bool isMatched {};

        //! Loop over index vector associated with letter
        //! Since index vector is ordered, could use binary search to decrease
        //! time complexity from O(t_size) to O(log(t_size))
        for (const auto matchIndex : letterIndicesTable[letter])
        {
            if (currMatchIndex < matchIndex)
            {
                currMatchIndex = matchIndex;
                isMatched      = true;
                break;
            }
        }

        if (not isMatched)
        {
            return false;
        }

    } // for (const auto letter : s)

    //! Consume all characters in the source string
    return true;

} // static bool isSubsequenceGreedyHashmap( ...

TEST(IsSubsequenceTest, SampleTest)
{
    EXPECT_TRUE(isSubsequenceDCGreedy("abc", "ahbgdc"));
    EXPECT_FALSE(isSubsequenceDCGreedy("axc", "ahbgdc"));

    EXPECT_TRUE(isSubsequenceTwoPtrs("abc", "ahbgdc"));
    EXPECT_FALSE(isSubsequenceTwoPtrs("axc", "ahbgdc"));

    EXPECT_TRUE(isSubsequenceGreedyHashmap("abc", "ahbgdc"));
    EXPECT_FALSE(isSubsequenceGreedyHashmap("axc", "ahbgdc"));
}