#include <gtest/gtest.h>

#include <algorithm>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

//! @class GraphFirstAttempt
//! @brief First attempt solution times out for Test case 5
class GraphFirstAttempt
{
public:
    GraphFirstAttempt()  = default;
    ~GraphFirstAttempt() = default;

    GraphFirstAttempt(int n)
        : n_ {n}
    {
        node_map_.reserve(n);
    }

    GraphFirstAttempt(const GraphFirstAttempt&) = default;
    GraphFirstAttempt(GraphFirstAttempt&&)      = default;
    GraphFirstAttempt& operator=(const GraphFirstAttempt&) = default;
    GraphFirstAttempt& operator=(GraphFirstAttempt&&) = default;

    void add_edge(int u, int v)
    {
        node_map_[u].emplace_back(v);
        node_map_[v].emplace_back(u);
    }

    //! @brief Helper function to calculate shortest dist between two nodes
    //! @param[in] start Starting node value
    //! @param[in] end   Ending node value
    //! @return Shortest distance between start and end nodes
    int calculate_shortest_distance(int start, int end)
    {
        //! Output shortest distance
        int shortest_dist {};
        
        //! Vector of nodes to search for end node,
        //! initialized to nodes connected to start
        auto nodes_todo = node_map_[start];
        
        //! If nodes_todo is empty, start is not connected
        //! If start == end then just return -1
        if (nodes_todo.empty() || start == end)
        {
            return -1;
        }

        //! Set of nodes already processed, initialized with start node
        std::unordered_set<int> nodes_visited {};
        std::ignore = nodes_visited.emplace(start);
        
        //! Number of nodes to process
        auto num_todo = static_cast<int>(nodes_todo.size());
        
        while (num_todo > 0)
        {
            //! Distance is same to all these nodes so increment by it
            shortest_dist += edge_length;
            
            auto end_it = std::find(nodes_todo.cbegin(),
                                    nodes_todo.cend(),
                                    end);
            if (end_it != nodes_todo.cend())
            {
                //! Found desired end node
                return shortest_dist;
            }

            //! Add connected nodes that haven't been
            //! processed yet for each node in nodes_todo
            for (int i = 0; i < num_todo; ++i)
            {
                for (const auto node : node_map_[nodes_todo[i]])
                {
                    if (not nodes_visited.emplace(node).second)
                    {
                        //! node was already visited, skip it
                        continue;
                    }
                    
                    nodes_todo.emplace_back(node);
                }
            }
            
            //! Remove first num_todo nodes that have been processed
            nodes_todo.erase(nodes_todo.begin(), nodes_todo.begin() + num_todo);
            
            //! Finally update num_todo
            num_todo = static_cast<int>(nodes_todo.size());
            
        } // while (num_todo > 0)
        
        //! If this point is reached then start
        //! is not connected to end so return -1
        return -1;

    } // int calculate_shortest_distance( ...

    std::vector<int> shortest_reach(int start)
    {
        //! Output vector of shortest distances
            std::vector<int> dist_vec(n_);
            
            //! Solution expects start to be in output vector
            for (int i = 0; i < n_; ++i)
            {
                dist_vec[i] = calculate_shortest_distance(start, i);
            }
            
            return dist_vec;

    } // std::vector<int> shortest_reach(int start)

private:
    //! Number of nodes in undirected graph
    int n_ {};
    
    //! Length of edge in graph
    static constexpr int edge_length {6};

    //! Unordered map where key is node 1 to n
    //! Value is vector of connected nodes
    std::unordered_map<int, std::vector<int>> node_map_ {};

}; // class GraphFirstAttempt

// Test case 0
TEST(GraphTest, TestCase0) {
    GraphFirstAttempt first_soln_1 {4};
    first_soln_1.add_edge(0, 1);
    first_soln_1.add_edge(0, 2);
    auto first_soln_dist = first_soln_1.shortest_reach(0);

    const std::vector<int> expected_dist_1 {-1, 6, 6, -1};
    EXPECT_TRUE(std::equal(first_soln_dist.cbegin(),
                           first_soln_dist.cend(),
                           expected_dist_1.cbegin()));

    GraphFirstAttempt first_soln_2 {3};
    first_soln_2.add_edge(1, 2);
    first_soln_dist = first_soln_2.shortest_reach(1);
    
    const std::vector<int> expected_dist_2 {-1, -1, 6};
    EXPECT_TRUE(std::equal(first_soln_dist.cbegin(),
                           first_soln_dist.cend(),
                           expected_dist_2.cbegin()));
}

// Test case 7
TEST(GraphTest, TestCase7) {
    GraphFirstAttempt first_soln {6};
    first_soln.add_edge(0, 1);
    first_soln.add_edge(1, 2);
    first_soln.add_edge(2, 3);
    first_soln.add_edge(0, 4);
    auto first_soln_dist = first_soln.shortest_reach(0);

    const std::vector<int> expected_dist {-1, 6, 12, 18, 6, -1};
    EXPECT_TRUE(std::equal(first_soln_dist.cbegin(),
                           first_soln_dist.cend(),
                           expected_dist.cbegin()));
}

// Test case 8
TEST(GraphTest, TestCase8) {
    GraphFirstAttempt first_soln {7};
    first_soln.add_edge(0, 1);
    first_soln.add_edge(0, 2);
    first_soln.add_edge(2, 3);
    first_soln.add_edge(1, 4);
    auto first_soln_dist = first_soln.shortest_reach(1);

    const std::vector<int> expected_dist {6, -1, 12, 18, 6, -1, -1};
    EXPECT_TRUE(std::equal(first_soln_dist.cbegin(),
                           first_soln_dist.cend(),
                           expected_dist.cbegin()));
}

