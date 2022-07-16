#include <gtest/gtest.h>

#include <string>

static std::string twoStrings(std::string s1, std::string s2)
{
    auto match_pos = s2.find_first_of(s1);
    return match_pos != std::string::npos ? "YES" : "NO";
}

// Try sample inputs given in problem description 
TEST(TwoStringsTest, SampleInputs) {
    // Sample input 0, share substring 'a'
    std::string s1 {"and"};
    std::string s2 {"art"};
    EXPECT_EQ("YES", twoStrings(s1, s2));

    // Sample input 1, do not share a substring
    s1 = "be";
    s2 = "cat";
    EXPECT_EQ("NO", twoStrings(s1, s2));

    // Sample input 2, share substrings "o" and "l"
    s1 = "hello";
    s2 = "world";
    EXPECT_EQ("YES", twoStrings(s1, s2));

    // Sample input 3, do not share a substring
    s1 = "hi";
    s2 = "world";
    EXPECT_EQ("NO", twoStrings(s1, s2));
}

// Try Sample Test case 1 before submission
TEST(TwoStringsTest, SampleTestCase1) {
    std::string s1 {"wouldyoulikefries"};
    std::string s2 {"abcabcabcabcabcabc"};
    EXPECT_EQ("NO", twoStrings(s1, s2));

    s1 = "hackerrankcommunity";
    s2 = "cdecdecdecde";
    EXPECT_EQ("YES", twoStrings(s1, s2));

    s1 = "jackandjill";
    s2 = "wentupthehill";
    EXPECT_EQ("YES", twoStrings(s1, s2));

    s1 = "writetoyourparents";
    s2 = "fghmqzldbc";
    EXPECT_EQ("NO", twoStrings(s1, s2));
}

// Try Sample Test case 2 before submission
TEST(TwoStringsTest, SampleTestCase2) {
    std::string s1 {"aardvark"};
    std::string s2 {"apple"};
    EXPECT_EQ("YES", twoStrings(s1, s2));

    s1 = "beetroot";
    s2 = "sandals";
    EXPECT_EQ("NO", twoStrings(s1, s2));
}