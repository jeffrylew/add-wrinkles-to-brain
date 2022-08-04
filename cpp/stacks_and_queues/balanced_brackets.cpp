#include <gtest/gtest.h>

#include <map>
#include <stack>
#include <string>

static std::string isBalanced(std::string s)
{
    // Map storing left bracket as key and right bracket as value
    std::map<char, char> brackets_map {{'{', '}'}, {'[', ']'}, {'(', ')'}};
    
    // Stack to store expected right brackets
    std::stack<char> expected_right_brackets {};
    
    auto char_it = s.cbegin();
    
    while (char_it != s.cend())
    {
        if (brackets_map.count(*char_it) > 0)
        {
            // Found a left bracket, add its expected right bracket to stack
            expected_right_brackets.emplace(brackets_map.at(*char_it));
        }
        else
        {
            // Found a right bracket
            
            // Check if it matches the expected right bracket
            if (expected_right_brackets.empty()
               || *char_it != expected_right_brackets.top())
            {
                // There are more right brackets than expected
                // or the current right bracket does not match
                // the expected one
                return "NO";
            }
            
            // Right bracket matches expected right bracket
            expected_right_brackets.pop();
            
        } // else -> if (brackets_map.count(*char_it) > 0)
        
        ++char_it;
        
    } // while (char_it != s.cend())
    
    // If stack isn't empty, string had fewer right brackets than expected
    return expected_right_brackets.empty() ? "YES" : "NO";

} // static std::string isBalanced( ...

// Test case 18
TEST(IsBalancedTest, TestCase18) {
    EXPECT_EQ("YES", isBalanced("{[()]}"));
    EXPECT_EQ("NO", isBalanced("{[(])}"));
    EXPECT_EQ("YES", isBalanced("{{[[(())]]}}"));
}

// Test case 19
TEST(IsBalancedTest, TestCase19) {
    EXPECT_EQ("YES", isBalanced("{{([])}}"));
    EXPECT_EQ("NO", isBalanced("{{)[](}}"));
}

// Test case 20
TEST(IsBalancedTest, TestCase20) {
    EXPECT_EQ("YES", isBalanced("{(([])[])[]}"));
    EXPECT_EQ("NO", isBalanced("{(([])[])[]]}"));
    EXPECT_EQ("YES", isBalanced("{(([])[])[]}[]"));
}