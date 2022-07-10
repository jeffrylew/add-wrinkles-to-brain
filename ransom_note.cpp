#include <gtest/gtest.h>

#include <algorithm>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

static std::string checkMagazine(std::vector<std::string> magazine,
                                 std::vector<std::string> note)
{
    // Map of word in note to num instances of word
    std::map<std::string, int> note_map {};
    std::for_each(note.cbegin(),
                  note.cend(),
                  [&](decltype(note)::const_reference word)
                  {
                      auto ret = note_map.emplace(word, 1);
                      if (not ret.second)
                      {
                          ++ret.first->second;
                      }
                  });
    
    // Iterate through words in magazine
    // If there is a word in the note that matches,
    // decrement the count in note_map.
    // If the num instances of a word reaches
    // zero in note_map, remove the word.
    //
    // If note_map become empty then the note was
    // successfully recreated from the magazine.
    //
    // If the magazine has been iterated through
    // completely and note_map is still not empty
    // then the ransom note cannot be replicated.
    for (const auto& word : magazine)
    {
        auto it = note_map.find(word);
        if (it != note_map.end())
        {
            // Decrement count
            --it->second;
            
            // If count is 0, remove word from note_map
            if (it->second == 0)
            {
                note_map.erase(it);
            }
        }
        
        // If all words in note have been accounted for,
        // return Yes and stop checking words in magazine
        if (note_map.empty())
        {
            return "Yes";
        }
    }
    
    // All words in note have not been accounted for
    // at this point so return No
    return "No";

} // static std::string checkMagazine( ...

//! @brief A solution from discussion section, slightly modified
static std::string checkMagazineDiscussionSolution(
    std::vector<std::string> magazine,
    std::vector<std::string> note)
{
    // Map of words in magazine and their corresponding counts
    std::unordered_map<std::string, int> magazine_map {};

    for (const auto& word : magazine)
    {
        ++magazine_map[word];
    }

    for (const auto& word : note)
    {
        if (magazine_map[word] > 0)
        {
            --magazine_map[word];
        }
        else
        {
            return "No";
        }
    }

    return "Yes";

} // static std::string checkMagazineDiscussionSolution( ...

// Try sample inputs given in problem description
TEST(CheckMagazineTest, SampleInputs) {
    // Sample input 0 (Test case 0)
    std::vector<std::string> magazine {
        "give", "me", "one", "grand", "today", "night"};
    std::vector<std::string> note {
        "give", "one", "grand", "today"};
    EXPECT_EQ("Yes", checkMagazine(magazine, note));
    EXPECT_EQ("Yes", checkMagazineDiscussionSolution(magazine, note));

    // Sample input 1 (Test case 20)
    magazine = {"two", "times", "three", "is", "not", "four"};
    note     = {"two", "times", "two", "is", "four"};
    EXPECT_EQ("No", checkMagazine(magazine, note));
    EXPECT_EQ("No", checkMagazineDiscussionSolution(magazine, note));

    // Sample input 2 (Test case 21)
    magazine = {"ive", "got", "a", "lovely", "bunch", "of", "coconuts"};
    note     = {"ive", "got", "some", "coconuts"};
    EXPECT_EQ("No", checkMagazine(magazine, note));
    EXPECT_EQ("No", checkMagazineDiscussionSolution(magazine, note));
}

// Test repeated words in magazine and note
TEST(CheckMagazineTest, RepeatedWords) {
    // Test repeated words, where magazine has more instances than note
    std::vector<std::string> magazine {"hello", "hello", "hello"};
    std::vector<std::string> note {"hello", "hello"};
    EXPECT_EQ("Yes", checkMagazine(magazine, note));
    EXPECT_EQ("Yes", checkMagazineDiscussionSolution(magazine, note));

    // Test repeated words, where note has more instances than magazine
    magazine = {"hello", "hello"};
    note     = {"hello", "hello", "hello"};
    EXPECT_EQ("No", checkMagazine(magazine, note));
    EXPECT_EQ("No", checkMagazineDiscussionSolution(magazine, note));
}