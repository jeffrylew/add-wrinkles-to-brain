#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Calculate median of spending data vector
//! @param[in] spend_data Vector of spending data passed by value
//! @return Median as a double
static double medianFirstAttempt(std::vector<int> spend_data)
{
    //! @details First attempt solution times out for Test cases 1-5

    const auto size = static_cast<int>(spend_data.size());
    
    // std::nth_element ensures nth element is in correct position
    // Elements before nth are le and after nth are ge
    // O(n) on average
    const auto n    = size / 2;
    auto       n_it = spend_data.begin() + n;
    std::nth_element(spend_data.begin(),
                     n_it,
                     spend_data.end());

    if (size % 2 != 0)
    {
        // Odd number of elements so n_it points to the median
        return static_cast<double>(*n_it);
    }
    
    // For even number of elements, need to get middle two
    // Get max value of elements before nth
    // std::max_element is O(n)
    auto n_prev_it = std::max_element(spend_data.begin(), n_it);
    
    return (*n_prev_it + *n_it) / 2.0;
    
} // static double medianFirstAttempt( ...

//! @brief Calculate median of sorted (ascending) spending data vector
//! @param[in] spend_data Reference to vector of sorted spending data
//! @pre spend_data is sorted in ascending order to nth element and is not empty
//! @return Median as a double
static double medianSecondAttempt(const std::vector<int>& spend_data)
{
    //! @details Second attempt solution still times out for Test cases 1-5

    const auto size = static_cast<int>(spend_data.size());
    
    // Find middle element at nth position (if size is odd)
    const auto n       = size / 2;
    const auto nth_ele = spend_data.at(static_cast<std::size_t>(n));

    if (size % 2 != 0)
    {
        // Odd number of elements so nth_ele is the median
        return static_cast<double>(nth_ele);
    }
    
    // For even number of elements, need to get middle two
    auto n_prev_ele = spend_data.at(static_cast<std::size_t>(n - 1));
    
    return (n_prev_ele + nth_ele) / 2.0;
    
} // static double medianSecondAttempt() ...

static int activityNotificationsFirstAttempt(std::vector<int> expenditure,
                                             int              d)
{
    //! @details First attempt solution times out for Test cases 1-5

    // Total number of notifications
    int n_notifications {};
    
    const auto e_size = static_cast<int>(expenditure.size());
    
    // Need at least d + 1 days of data
    if (e_size < d + 1)
    {
        return n_notifications;
    }
    
    // Iterators to begin and end of trailing days data
    auto trailing_days_begin = expenditure.cbegin();
    auto trailing_days_end   = expenditure.cbegin() + d;
    
    while (trailing_days_end != expenditure.cend())
    {
        // Amount spent on current day (has trailing days d before it)
        const auto current_day_spend = static_cast<double>(*trailing_days_end);
        
        // Median of trailing days d
        const auto median_spend =
            medianFirstAttempt(std::vector<int>(trailing_days_begin,
                                                trailing_days_end));
        
        if (2.0 * median_spend <= current_day_spend)
        {
            ++n_notifications;
        }
        
        ++trailing_days_begin;
        ++trailing_days_end;
    }
    
    return n_notifications;

} // static int activityNotificationsFirstAttempt( ...

static int activityNotificationsSecondAttempt(std::vector<int> expenditure,
                                              int              d)
{
    //! @details Second attempt solution still times out for Test cases 1-5

    // Total number of notifications
    int n_notifications {};
    
    const auto e_size = static_cast<int>(expenditure.size());
    
    // Need at least d + 1 days of data
    if (e_size < d + 1)
    {
        return n_notifications;
    }
    
    // Vector to hold trailing days data up to position of median + 1
    std::vector<int> median_trailing_days(static_cast<std::size_t>(d / 2 + 1));

    // Iterators to begin and end of trailing days data
    auto trailing_days_begin = expenditure.cbegin();
    auto trailing_days_end   = expenditure.cbegin() + d;
    
    while (trailing_days_end != expenditure.cend())
    {
        // Amount spent on current day (has trailing days d before it)
        const auto current_day_spend = static_cast<double>(*trailing_days_end);
        
        // Sort trailing days range
        std::partial_sort_copy(trailing_days_begin,
                               trailing_days_end,
                               median_trailing_days.begin(),
                               median_trailing_days.end());

        // Median of trailing days d
        double median_spend {};
        if (d % 2 != 0)
        {
            median_spend = static_cast<double>(median_trailing_days.back());
        }
        else
        {
            median_spend = static_cast<double>(
                median_trailing_days.back()
                + *(--median_trailing_days.end()))
                / 2.0;
        }
        
        if (2.0 * median_spend <= current_day_spend)
        {
            ++n_notifications;
        }
        
        ++trailing_days_begin;
        ++trailing_days_end;
    }
    
    return n_notifications;

} // static int activityNotificationsSecondAttempt( ...

// Test case 0
TEST(ActivityNotificationsTest, TestCase0) {
    EXPECT_EQ(
        2, activityNotificationsFirstAttempt({2, 3, 4, 2, 3, 6, 8, 4, 5}, 5));

    EXPECT_EQ(
        2, activityNotificationsSecondAttempt({2, 3, 4, 2, 3, 6, 8, 4, 5}, 5));
}

// Test case 6
TEST(ActivityNotificationsTest, TestCase6) {
    EXPECT_EQ(0, activityNotificationsFirstAttempt({1, 2, 3, 4, 4}, 4));

    EXPECT_EQ(0, activityNotificationsSecondAttempt({1, 2, 3, 4, 4}, 4));
}

// Test case 7
TEST(ActivityNotificationsTest, TestCase7) {
    EXPECT_EQ(1, activityNotificationsFirstAttempt({10, 20, 30, 40, 50}, 3));

    EXPECT_EQ(1, activityNotificationsSecondAttempt({10, 20, 30, 40, 50}, 3));
}