#include <gtest/gtest.h>

#include <memory>
#include <stack>

class MyQueue
{
public:
    MyQueue()          = default;
    virtual ~MyQueue() = default;

    virtual void push(int x) = 0;
    virtual void pop()       = 0;
    virtual int  front()     = 0;

    std::stack<int> stack_newest_on_top {};
    std::stack<int> stack_oldest_on_top {};
};

//! @brief First attempt solution times out for Test cases 6-15
class MyQueueFirstAttempt : public MyQueue
{  
public:
    MyQueueFirstAttempt()           = default;
    ~MyQueueFirstAttempt() override = default;

    void push(int x) override
    {
        // Move oldest items to bottom of stack_newest_on_top
        while (not stack_oldest_on_top.empty())
        {
            stack_newest_on_top.emplace(stack_oldest_on_top.top());
            stack_oldest_on_top.pop();
        }
        
        // Add newest item
        stack_newest_on_top.emplace(x);
        
        // Move newest items to bottom of stack_oldest_on_top
        while (not stack_newest_on_top.empty())
        {
            stack_oldest_on_top.emplace(stack_newest_on_top.top());
            stack_newest_on_top.pop();
        }
    }

    void pop() override
    {
        stack_oldest_on_top.pop();
    }

    int front() override
    {
        return stack_oldest_on_top.top();
    }

}; // class MyQueueFirstAttempt : ...

//! @brief Solution with hint from discussion section
class MyQueueDiscussionSolution : public MyQueue
{  
public:
    MyQueueDiscussionSolution()           = default;
    ~MyQueueDiscussionSolution() override = default;

    void push(int x) override
    {
        // Add newest item
        stack_newest_on_top.emplace(x);
    }

    void pop() override
    {
        if (stack_oldest_on_top.empty())
        {
            // Move newest items to bottom of stack_oldest_on_top
            while (not stack_newest_on_top.empty())
            {
                stack_oldest_on_top.emplace(stack_newest_on_top.top());
                stack_newest_on_top.pop();
            }
        }
        
        // Pop oldest item
        stack_oldest_on_top.pop();
    }

    int front() override
    {
        if (stack_oldest_on_top.empty())
        {
            // Move newest items to bottom of stack_oldest_on_top
            while (not stack_newest_on_top.empty())
            {
                stack_oldest_on_top.emplace(stack_newest_on_top.top());
                stack_newest_on_top.pop();
            }
        }
        return stack_oldest_on_top.top();
    }

}; // class MyQueueDiscussionSolution : ...

// Test case 0
TEST(MyQueueTest, TestCase0) {
    std::unique_ptr<MyQueue> q {nullptr};
    
    q = std::make_unique<MyQueueFirstAttempt>();
    q->push(42);
    q->pop();
    q->push(14);
    EXPECT_EQ(14, q->front());
    q->push(28);
    EXPECT_EQ(14, q->front());
    q->push(60);
    q->push(78);
    q->pop();
    q->pop();
    q.reset();

    q = std::make_unique<MyQueueDiscussionSolution>();
    q->push(42);
    q->pop();
    q->push(14);
    EXPECT_EQ(14, q->front());
    q->push(28);
    EXPECT_EQ(14, q->front());
    q->push(60);
    q->push(78);
    q->pop();
    q->pop();
}

// Test case 16
TEST(MyQueueTest, TestCase16) {
    std::unique_ptr<MyQueue> q {nullptr};
    
    q = std::make_unique<MyQueueFirstAttempt>();
    q->push(15);
    q->push(17);
    EXPECT_EQ(15, q->front());
    q->push(25);
    q->pop();
    EXPECT_EQ(17, q->front());
    q->pop();
    EXPECT_EQ(25, q->front());
    q.reset();

    q = std::make_unique<MyQueueDiscussionSolution>();
    q->push(15);
    q->push(17);
    EXPECT_EQ(15, q->front());
    q->push(25);
    q->pop();
    EXPECT_EQ(17, q->front());
    q->pop();
    EXPECT_EQ(25, q->front());
}

// Test case 17
TEST(MyQueueTest, TestCase17) {
    std::unique_ptr<MyQueue> q {nullptr};
    
    q = std::make_unique<MyQueueFirstAttempt>();
    q->push(12);
    q->push(14);
    EXPECT_EQ(12, q->front());
    q->pop();
    EXPECT_EQ(14, q->front());
    q->push(71);
    q->push(63);
    EXPECT_EQ(14, q->front());
    q.reset();

    q = std::make_unique<MyQueueDiscussionSolution>();
    q->push(12);
    q->push(14);
    EXPECT_EQ(12, q->front());
    q->pop();
    EXPECT_EQ(14, q->front());
    q->push(71);
    q->push(63);
    EXPECT_EQ(14, q->front());
}