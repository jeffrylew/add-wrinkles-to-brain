#include <gtest/gtest.h>

#include <algorithm>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

/*
//! Type alias for 2D vectors for horizontal and vertical words
using Vecs_ref_t = std::tuple<std::vector<std::vector<char&>>,
                              std::vector<std::vector<char&>>>;
                              */

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
/*
//! @brief Reset 2D vector of char refs to crossword to contain original '-'
//! @param[out] tuple_vecs Reference to Vecs_ref_t
static void reset(Vecs_ref_t& tuple_vecs)
{
    auto& horiz_words = std::get<0>(tuple_vecs);
    auto& vert_words  = std::get<1>(tuple_vecs);

    for (auto& char_vec : horiz_words)
    {
        std::fill(char_vec.begin(), char_vec.end(), '-');
    }

    for (auto& char_vec : vert_words)
    {
        std::fill(char_vec.begin(), char_vec.end(), '-');
    }
}

//! @brief Populate vecs_ref from crossword
//! @param[in,out] crossword Reference to vector of 10 strings
//! @param[out]    vecs_ref  Reference to Vecs_ref_t
static void populate_refs(std::vector<std::string>& crossword,
                          Vecs_ref_t&               vecs_ref)
{
    //! Vector of words in rows
    auto& row_words = std::get<0>(vecs_ref);
    
    //! Vector of words in cols
    auto& col_words = std::get<1>(vecs_ref);
    
    //! Populate row_words
    for (int row = 0; row < crossword.size(); ++row)
    {
        //! Flag to keep track if a new word has been found in the row
        bool new_word_in_row {};

        for (int col = 0; col < crossword.front().size(); ++col)
        {
            if ('-' != crossword[row][col])
            {
                new_word_in_row = false;
                continue;
            }

            if (not new_word_in_row)
            {
                //! The first time hyphen is encountered, create new vector
                //! containing crossword[row][col]. Set new_word_in_row to true
                row_words.emplace_back({crossword[row][col]});
                new_word_in_row = true;
            }
            else
            {
                //! Found hyphen but already created new vector
                //! Just append hyphen to existing vector
                row_words.back().emplace_back(crossword[row][col]);
            }
            
        } // for (int col = 0; ...

    } // for (int row = 0; ...

    //! Populate col_words
    for (int col = 0; col < crossword.front().size(); ++col)
    {
        //! Flag to keep track if a new word has been found in the column
        bool new_word_in_col {};

        for (int row = 0; row < crossword.size(); ++row)
        {
            if ('-' != crossword[row][col])
            {
                new_word_in_col = false;
                continue;
            }

            if (not new_word_in_false)
            {
                //! The first time hyphen is encountered, create new vector
                //! containing crossword[row][col]. Set new_word_in_col to true
                col_words.emplace_back({crossword[row][col]});
                new_word_in_col = true;
            }
            else
            {
                //! Found hyphen but already created new vector
                //! Just append hyphen to existing vector
                col_words.back().emplace_back(crossword[row][col]);
            }

        } // for (int row = 0; ...

    } // for (int col = 0; ...

} // static Vecs_ref_t populate_refs( ...

static void crosswordPuzzleFARecursive(std::vector<std::string>  crossword_in,
                                       std::vector<std::string>  words_in,
                                       std::vector<std::string>& crossword_out)
{
    //! Flag indicating if crossword is completely filled out
    //! crossword guaranteed to be not empty by problem design
    bool crossword_filled {true};
    for (const auto& str : crossword_out)
    {
        crossword_filled =
            crossword_filled && std::none_of(str.cbegin(),
                                             str.cend(),
                                             [](char c) -> bool {
                                                return c == '-';
                                             });
        
        if (not crossword_filled)
        {
            //! Encountered hyphen, crossword not completely filled yet
            //! so stop checking
            break;
        }
    }

    //! Stop recursion if crossword is filled
    if (crossword_filled)
    {
        return;
    }

    //! Crossword not completely filled but no more words to process
    //! Reset crossword_out
    if (words_in.empty())
    {
        crossword_out = crossword_in;
        return;
    }
    
    //! This is definitely incorrect... Need to perform backtracking and
    //! resetting if word does not fit into vecs_ref element. Should also
    //! remove elements from words_in as part of recursive logic
    Vecs_ref_t vecs_ref {};
    populate_refs(crossword_out, vecs_ref);

    for (const auto& word : words_in)
    {
        auto& horiz_words = std::get<0>(vecs_ref);
        for (auto& char_vec : horiz_words)
        {
            if (word.size() != char_vec.size())
            {
                continue;
            }
            
            for (int i = 0; i < char_vec.size(); ++i)
            {
                if (char_vec[i] != '-' && char_vec[i] != word[i])
                {
                    break;
                }
                char_vec[i] = word[i];
            }
        }

        auto& vert_words = std::get<1>(vecs_ref);
        for (auto& char_vec : vert_words)
        {
            if (word.size() != char_vec.size())
            {
                continue;
            }
            
            for (int i = 0; i < char_vec.size(); ++i)
            {
                if (char_vec[i] != '-' && char_vec[i] != word[i])
                {
                    break;
                }
                char_vec[i] = word[i];
            }
        }
    }

} // static void crosswordPuzzleFARecursive( ...

//! @brief First attempt solution
static std::vector<std::string> crosswordPuzzleFirstAttempt(
    std::vector<std::string> crossword,
    std::string              words)
{
    const auto words_in      = split(words, ';');
    auto       crossword_out = crossword;

    crosswordPuzzleFARecursive(crossword, words_in, crossword_out);
    return crossword_out;

} // std::vector<std::string> crosswordPuzzleFirstAttempt( ...
*/
//! @brief Recursive helper function for discussion solution
//! @param[in,out] crossword Reference to vector of strings containing crossword
//! @param[in,out] words     Reference to vector of strings containing words
//! @return True if words list has been exhausted
static bool crosswordPuzzleDS(std::vector<std::string>& crossword,
                              std::vector<std::string>& words)
{
    auto try_place = [&](std::size_t i, std::size_t j, bool r) -> bool {
        auto word = words.back();

        if ((r ? j : i) + word.size() > 10ULL)
        {
            return false;
        }
        
        for (std::size_t k = 0; k < word.size(); ++k)
        {
            if (crossword[r ? i : i + k][r ? j + k : j] != '-'
                && crossword[r ? i : i + k][r ? j + k : j] != word[k])
            {
                return false;
            }
        }
        
        auto crossword_copy = crossword;
        for (std::size_t k = 0; k < word.size(); ++k)
        {
            crossword[r ? i : i + k][r ? j + k : j] = word[k];
        }
        
        words.pop_back();
        bool success = crosswordPuzzleDS(crossword, words);
        words.push_back(word);
        if (not success)
        {
            crossword = crossword_copy;
        }
        
        return success;

    }; // auto try_place = ...

    if (words.empty())
    {
        return true;
    }
    
    for (std::size_t i = 0; i < 10ULL; ++i)
    {
        for (std::size_t j = 0; j < 10ULL; ++j)
        {
            //! By row
            if (try_place(i, j, true))
            {
                return true;
            }
            
            //! By col
            if (try_place(i, j, false))
            {
                return true;
            }
        }
    }
    
    return false;

} // static bool crosswordPuzzleDS( ...

//! @brief Solution from HR discussion section
static std::vector<std::string> crosswordPuzzleDS(
    std::vector<std::string> crossword,
    std::string              words)
{
    auto word_vec = split(words, ';');
    crosswordPuzzleDS(crossword, word_vec);
    return crossword;
}

// Test case 0
TEST(CrosswordPuzzleTest, TestCase0) {
    std::vector<std::string> input_crossword {
        "+-++++++++",
        "+-++++++++",
        "+-++++++++",
        "+-----++++",
        "+-+++-++++",
        "+-+++-++++",
        "+++++-++++",
        "++------++",
        "+++++-++++",
        "+++++-++++"};

    std::string input_words {"LONDON;DELHI;ICELAND;ANKARA"};

    const std::vector<std::string> expected_output {
        "+L++++++++",
        "+O++++++++",
        "+N++++++++",
        "+DELHI++++",
        "+O+++C++++",
        "+N+++E++++",
        "+++++L++++",
        "++ANKARA++",
        "+++++N++++",
        "+++++D++++"};
    
    const auto result = crosswordPuzzleDS(input_crossword, input_words);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));
}

// Test case 1
TEST(CrosswordPuzzleTest, TestCase1) {
    std::vector<std::string> input_crossword {
        "+-++++++++",
        "+-++++++++",
        "+-------++",
        "+-++++++++",
        "+-++++++++",
        "+------+++",
        "+-+++-++++",
        "+++++-++++",
        "+++++-++++",
        "++++++++++"};

    std::string input_words {"AGRA;NORWAY;ENGLAND;GWALIOR"};

    const std::vector<std::string> expected_output {
        "+E++++++++",
        "+N++++++++",
        "+GWALIOR++",
        "+L++++++++",
        "+A++++++++",
        "+NORWAY+++",
        "+D+++G++++",
        "+++++R++++",
        "+++++A++++",
        "++++++++++"};
    
    const auto result = crosswordPuzzleDS(input_crossword, input_words);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));
}

