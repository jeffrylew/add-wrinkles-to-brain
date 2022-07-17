#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <numeric>
#include <string>

//! @brief Get index in array corresponding to c
//! @param[in] c Lowercase char with ascii value in [97, 122]
//! @pre c is a lowercase character
//! @return Index of c in array representing lowercase characters
static std::size_t getIdx(char c)
{
    return static_cast<std::size_t>(static_cast<int>(c) - 97);
}

//! @brief First attempt solution fails Test cases 4, 7, 13, and 16
static std::string isValidFirstAttempt(std::string s)
{
    // Array of lowercase character counts
    // ascii characters a to z map to indices 0 to 25
    std::array<int, 26ULL> char_counts {{}};
    
    // Populate char_counts with character counts in s
    for (const auto c : s)
    {
        ++char_counts.at(getIdx(c));
    }
    
    // Get iterator to first non-zero count
    auto first_non_zero_it = std::find_if(char_counts.cbegin(),
                                          char_counts.cend(),
                                          [](int count) -> bool {
                                              return count != 0;
                                          });

    // Get iterator to minimum count that is non-zero
    auto min_it = std::min_element(first_non_zero_it,
                                   char_counts.cend(),
                                   [](int lhs, int rhs) -> bool {
                                       return lhs != 0 && lhs < rhs;
                                   });
    
    if (min_it == char_counts.cend())
    {
        // This should never happen since input s cannot be empty
        return "NO";
    }
    else
    {
        // Normalize non-zero values in char_counts by minimum count
        const auto non_zero_min = *min_it;
        std::transform(char_counts.begin(),
                       char_counts.end(),
                       char_counts.begin(),
                       [=](int count) -> int {
                           return (count == 0) ? 0 : count - non_zero_min;
                       });
                       
        // If sum of elements in char_counts is more than 1 then invalid
        return (std::accumulate(char_counts.cbegin(),
                                char_counts.cend(),
                                0) < 2) ? "YES" : "NO";
    }

} // static std::string isValidFirstAttempt( ...

//! @brief Second attempt solution fails Test cases 7 and 13
static std::string isValidSecondAttempt(std::string s)
{
    // Array of lowercase character counts
    // ascii characters a to z map to indices 0 to 25
    std::array<int, 26ULL> char_counts {{}};
    
    // Populate char_counts with character counts in s
    for (const auto c : s)
    {
        ++char_counts.at(getIdx(c));
    }
    
    // Get iterator to first non-zero count
    auto first_non_zero_it = std::find_if(char_counts.cbegin(),
                                          char_counts.cend(),
                                          [](int count) -> bool {
                                              return count != 0;
                                          });

    // Get iterator to minimum count that is non-zero
    auto min_it = std::min_element(first_non_zero_it,
                                   char_counts.cend(),
                                   [](int lhs, int rhs) -> bool {
                                       return lhs != 0 && lhs < rhs;
                                   });
                                   
    // Get iterator to maximum count that is non-zero
    // Note: Could use one loop to get min/max but this is convenient
    auto max_it = std::max_element(first_non_zero_it, char_counts.cend());
    
    if (min_it != char_counts.cend() && max_it != char_counts.cend())
    {
        // Normalize non-zero values in char_counts by min/max counts
        const auto non_zero_min = *min_it;
        const auto non_zero_max = *max_it;
        
        // Arrays to hold char_counts normalized by min/max counts
        std::array<int, 26ULL> normalized_by_min {{}};
        std::array<int, 26ULL> normalized_by_max {{}};
        
        std::transform(char_counts.begin(),
                       char_counts.end(),
                       normalized_by_min.begin(),
                       [=](int count) -> int {
                           return (count == 0) ? 0 : count - non_zero_min;
                       });
                        
        std::transform(char_counts.begin(),
                       char_counts.end(),
                       normalized_by_max.begin(),
                       [=](int count) -> int {
                           return (count == 0) ? 0 : count - non_zero_max;
                       });
                        
        // If sum of elements in normalized_by_min is less than 2 OR if sum
        // of elements in normalized_by_max is greater than -2 then valid
        if (std::accumulate(normalized_by_min.cbegin(),
                            normalized_by_min.cend(),
                            0) < 2
            || std::accumulate(normalized_by_max.cbegin(),
                               normalized_by_max.cend(),
                               0) > -2)
        {
            return "YES";
        }
        
    } // if (min_it != char_counts.cend() && ...

    return "NO";

} // static std::string isValidSecondAttempt( ...

// Test case 0
TEST(IsValidTest, TestCase0) {
    EXPECT_EQ("NO", isValidFirstAttempt("aabbcd"));

    EXPECT_EQ("NO", isValidSecondAttempt("aabbcd"));
}

// Test case 1
TEST(IsValidTest, TestCase1) {
    EXPECT_EQ("NO", isValidFirstAttempt("aabbccddeefghi"));

    EXPECT_EQ("NO", isValidSecondAttempt("aabbccddeefghi"));
}

// Test case 4, first solution failed this along with Test cases 7, 13, and 16
TEST(IsValidTest, TestCase4) {
    EXPECT_NE("YES", isValidFirstAttempt("aabbc"));

    EXPECT_EQ("YES", isValidSecondAttempt("aabbc"));
}

// Test case 7, first and second attempt solutions fail this
TEST(IsValidTest, TestCase7) {
    // 111 instances of a thru i and 1 instance of n
    constexpr const char* test_case_7_str {
        "ibfdgaeadiaefgbhbdghhhbgdfgeiccbiehhfcggchgghadhdhagfbahhddgghbdehidbibaeaagaeeigffcebfbaieggabcfbiiedcabfihchdfabifahcbhagccbdfifhghcadfiadeeaheeddddiecaicbgigccageicehfdhdgafaddhffadigfhhcaedcedecafeacbdacgfgfeeibgaiffdehigebhhehiaahfidibccdcdagifgaihacihadecgifihbebffebdfbchbgigeccahgihbcbcaggebaaafgfedbfgagfediddghdgbgehhhifhgcedechahidcbchebheihaadbbbiaiccededchdagfhccfdefigfibifabeiaccghcegfbcghaefifbachebaacbhbfgfddeceababbacgffbagidebeadfihaefefegbghgddbbgddeehgfbhafbccidebgehifafgbghafacgfdccgifdcbbbidfifhdaibgigebigaedeaaiadegfefbhacgddhchgcbgcaeaieiegiffchbgbebgbehbbfcebciiagacaiechdigbgbghefcahgbhfibhedaeeiffebdiabcifgccdefabccdghehfibfiifdaicfedagahhdcbhbicdgibgcedieihcichadgchgbdcdagaihebbabhibcihicadgadfcihdheefbhffiageddhgahaidfdhhdbgciiaciegchiiebfbcbhaeagccfhbfhaddagnfieihghfbaggiffbbfbecgaiiidccdceadbbdfgigibgcgchafccdchgifdeieicbaididhfcfdedbhaadedfageigfdehgcdaecaebebebfcieaecfagfdieaefdiedbcadchabhebgehiidfcgahcdhcdhgchhiiheffiifeegcfdgbdeffhgeghdfhbfbifgidcafbfcd"};

    EXPECT_NE("YES", isValidFirstAttempt(test_case_7_str));

    EXPECT_NE("YES", isValidSecondAttempt(test_case_7_str));
}

// Test case 18
TEST(IsValidTest, TestCase18) {
    EXPECT_EQ("YES", isValidFirstAttempt("abcdefghhgfedecba"));

    EXPECT_EQ("YES", isValidSecondAttempt("abcdefghhgfedecba"));
}