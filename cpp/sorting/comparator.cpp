#include <gtest/gtest.h>

#include <string>

struct Player
{
    Player() = default;
    Player(const std::string& name_in, int score_in)
        : score {score_in}
        , name {name_in}
    {
    }
    ~Player() = default;

    int         score {};
    std::string name {};
};

static int comparator(Player a, Player b)
{
    if (a.score == b.score)
        {
            const auto name_compare = a.name.compare(b.name);
            if (name_compare == 0)
            {
                return 0;
            }
            
            // If a.name > b.name, return -1
            return (name_compare < 0) ? 1 : -1;
        }

        // If a.score < b.score, return -1
        return (a.score > b.score) ? 1 : -1;
}

// Test case 0
TEST(ComparatorTest, TestCase0) {
    Player p1 {"aleksa", 150};
    Player p2 {"amy", 100};
    Player p3 {"david", 100};
    Player p4 {"aakansha", 75};
    Player p5 {"heraldo", 50};

    EXPECT_EQ(1, comparator(p1, p2));
    EXPECT_EQ(1, comparator(p2, p3));
    EXPECT_EQ(1, comparator(p3, p4));
    EXPECT_EQ(1, comparator(p4, p5));
}

// Test case 6
TEST(ComparatorTest, TestCase6) {
    Player p1 {"jones", 20};
    Player p2 {"smith", 20};
    Player p3 {"jones", 15};

    EXPECT_EQ(1, comparator(p1, p2));
    EXPECT_EQ(1, comparator(p2, p3));
}

// Test case 7
TEST(ComparatorTest, TestCase7) {
    Player p1 {"davis", 20};
    Player p2 {"davis", 15};
    Player p3 {"edgehill", 15};
    Player p4 {"davis", 10};

    EXPECT_EQ(1, comparator(p1, p2));
    EXPECT_EQ(1, comparator(p2, p3));
    EXPECT_EQ(1, comparator(p3, p4));
}