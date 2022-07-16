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

//! @brief Calculate twice the median of d trailing days expenditures
//! @param[in] trailing_days_count Vector of trailing days expenditures counts
//! @param[in] d                   Required number of trailing days of data
//! @pre trailing_days_count has size 201ULL, is not empty, and not all zeros
//! @return Twice the median as an int
static int twiceMedian(std::vector<int> trailing_days_count, int d)
{
    // Prefix sum determines position range for expenditure with value of i
    // O(k = 201), i.e. the range of possible expenditure values
    for (std::size_t i = 1ULL; i < trailing_days_count.size(); ++i)
    {
        trailing_days_count.at(i) += trailing_days_count.at(i - 1ULL);
    }
    
    if (d % 2 != 0)
    {
        // If trailing days is odd, return twice the middle index
        // The middle index is determined by comparing with the cumulative count
        // The indices in trailing_days_count are the expenditure values
        const int days_to_median {d / 2 + 1};
        
        // Get iterator to element in trailing_days_count where median would be
        auto median_it = std::find_if(trailing_days_count.cbegin(),
                                      trailing_days_count.cend(),
                                      [=](int accum_days) -> bool {
                                          return days_to_median <= accum_days;
                                      });

        // Using std::distance is O(1) for random access iterators (else O(n))
        // Returning 0 shouldn't happen
        return (median_it == trailing_days_count.cend()) ? 0
            : 2 * std::distance(trailing_days_count.cbegin(), median_it);

        /*
         * Equivalent logic from discussion section
         *
        for (std::size_t i = 0; i < trailing_days_count.size(); ++i)
        {
            if (num_days_to_median <= trailing_days_count.at(i))
            {
                return 2 * i;
            }
        }
        return 0;
        */
    }
    
    // Trailing days is even, return sum of two expenditures that form median
    const int days_before_median {d / 2};
    const int day_after_median {days_before_median + 1};

    // Get iterator to element in trailing_days_counts corresponding to
    // expenditure just before median value
    auto before_it = std::find_if(trailing_days_count.cbegin(),
                                  trailing_days_count.cend(),
                                  [=](int accum_days) -> bool {
                                      return days_before_median <= accum_days;
                                  });

    // Get iterator to element in trailing_days_counts corresponding to
    // expenditure just after median value
    auto after_it = std::find_if(before_it,
                                 trailing_days_count.cend(),
                                 [=](int accum_days) -> bool {
                                     return day_after_median <= accum_days;
                                 });
    
    // Using std::distance is O(1) for random access iterators (else O(n))
    // Returning 0 shouldn't happen
    return (after_it == trailing_days_count.cend()) ? 0
        : std::distance(trailing_days_count.cbegin(), before_it)
        + std::distance(trailing_days_count.cbegin(), after_it);

} // static int twiceMedian( ...

//! @brief Solution with hints from discussion section
//! @param[in] expenditure Vector of total daily expenditures over n days
//! @param[in] d           Required number of trailing days of data
//! @return Number of notifications client will receive over n days
static int activityNotificationsDiscussionHint(std::vector<int> expenditure,
                                               int              d)
{
    // Total number of notifications
    int n_notifications {};
    
    const auto e_size     = static_cast<int>(expenditure.size());
    const auto unsigned_d = static_cast<std::size_t>(d);

    // Need at least d + 1 days of data
    if (e_size < unsigned_d + 1ULL)
    {
        return n_notifications;
    }
    
    // Vector to store frequencies of expenditures within last d trailing days
    // From the problem description, we know the maximum expenditure is 200 in
    // one day, which allows usage of counting sort
    // Trailing days indices will map to range of expenditure values
    std::vector<int> trailing_days_count(201ULL);

    // Initialize histogram of expenditures in trailing_days_count
    for (std::size_t i = 0; i < unsigned_d; ++i)
    {
        ++trailing_days_count.at(static_cast<std::size_t>(expenditure.at(i)));
    }

    // Determine number of notifications and update trailing_days_count
    for (std::size_t i = unsigned_d; i < e_size; ++i)
    {
        const auto threshold = twiceMedian(trailing_days_count, d);
        if (expenditure.at(i) >= threshold)
        {
            ++n_notifications;
        }
        
        // Update trailing_days_count
        ++trailing_days_count.at(static_cast<std::size_t>(expenditure.at(i)));
        --trailing_days_count.at(
            static_cast<std::size_t>(expenditure.at(i - unsigned_d)));
    }
    
    return n_notifications;

} // static int activityNotificationsDiscussionHint( ...

// Test case 0
TEST(ActivityNotificationsTest, TestCase0) {
    EXPECT_EQ(
        2, activityNotificationsFirstAttempt({2, 3, 4, 2, 3, 6, 8, 4, 5}, 5));

    EXPECT_EQ(
        2, activityNotificationsSecondAttempt({2, 3, 4, 2, 3, 6, 8, 4, 5}, 5));

    EXPECT_EQ(
        2, activityNotificationsDiscussionHint({2, 3, 4, 2, 3, 6, 8, 4, 5}, 5));
}

// Test case 6
TEST(ActivityNotificationsTest, TestCase6) {
    EXPECT_EQ(0, activityNotificationsFirstAttempt({1, 2, 3, 4, 4}, 4));

    EXPECT_EQ(0, activityNotificationsSecondAttempt({1, 2, 3, 4, 4}, 4));

    EXPECT_EQ(0, activityNotificationsDiscussionHint({1, 2, 3, 4, 4}, 4));
}

// Test case 7
TEST(ActivityNotificationsTest, TestCase7) {
    EXPECT_EQ(1, activityNotificationsFirstAttempt({10, 20, 30, 40, 50}, 3));

    EXPECT_EQ(1, activityNotificationsSecondAttempt({10, 20, 30, 40, 50}, 3));

    EXPECT_EQ(1, activityNotificationsDiscussionHint({10, 20, 30, 40, 50}, 3));
}
