#include <gtest/gtest.h>

#include <queue>
#include <vector>

static int maximumToys(std::vector<int> prices, int k)
{
    // Total amount spent
    int money_spent {};

    // Keep track of the prices of gifts Mark can buy
    std::priority_queue<int> prices_of_buyable_gifts {};

    for (const auto price : prices)
    {
        if (price > k)
        {
            // Price of single item is more than entire budget, skip it
            continue;
        }

        // If buying this gift is still within budget, add it to priority_queue
        // and update money_spent
        if (money_spent + price <= k)
        {
            prices_of_buyable_gifts.emplace(price);
            money_spent += price;
        }
        else
        {
            // If price of current gift is less than price of most costly gift,
            // replace latter with former in priority_queue and update total
            // If not, do not buy current gift
            const auto most_costly_gift_price = prices_of_buyable_gifts.top();
            if (price < most_costly_gift_price)
            {
                money_spent = money_spent - most_costly_gift_price + price;
                prices_of_buyable_gifts.pop();
                prices_of_buyable_gifts.emplace(price);
            }
        }
        
    } // for (const auto price : prices)

    return static_cast<int>(prices_of_buyable_gifts.size());

} // static int maximumToys( ...

// Test case 0
TEST(MaximumToysTest, TestCase0) {
    EXPECT_EQ(4, maximumToys({1, 12, 5, 111, 200, 1000, 10}, 50));
}

// Test case 16
TEST(MaximumToysTest, TestCase16) {
    EXPECT_EQ(3, maximumToys({1, 2, 3, 4}, 7));
}

// Test case 17
TEST(MaximumToysTest, TestCase17) {
    EXPECT_EQ(3, maximumToys({3, 7, 2, 9, 4}, 15));
}