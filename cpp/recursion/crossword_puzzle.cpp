#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

//! @brief Tokenize input string into vector
//! @param[in] input String to split
//! @param[in] delim Character delimiter
//! @return Vector of tokenized strings
static std::vector<std::string> split(std::string input, char delim)
{
    //! @details https://stackoverflow.com/questions/14265581/
    //!          parse-split-a-string-in-c-using-string-delimiter-standard-c

    std::vector<std::string> output {};
    std::istringstream       isstream {input};
    std::string              item;

    while (std::getline(isstream, item, delim))
    {
        output.push_back(item);
    }

    return output;

} // static std::vector<std::string> split( ...

//! @brief First attempt solution
static std::vector<std::string> crosswordPuzzleFirstAttempt(
    std::vector<std::string> crossword,
    std::string              words)
{

} // std::vector<std::string> crosswordPuzzleFirstAttempt( ...

// Test case X
TEST(CrosswordPuzzleTest, TestCaseX) {

}

// Test case Y
TEST(CrosswordPuzzleTest, TestCaseY) {

}

