#include "Queue.h"

#include <gtest.h>

TEST(Queue, can_create_queue)
{
    ASSERT_NO_THROW(TQueue<int>(5));
}

TEST(Queue, cant_create_queue_with_zero_capacity)
{
    ASSERT_ANY_THROW(TQueue<int>(0));
}

TEST(Queue, can_push_item_to_queue)
{
    TQueue<int> s(5);
    ASSERT_NO_THROW(s.push(1));
}


TEST(Queue, can_pop_item_from_queue)
{
    TQueue<int> s(5);
    s.push(1);
    int number = s.pop();
    EXPECT_EQ(number, 1);
}

TEST(Queue, default_queue_is_empty)
{
    TQueue<int> s(5);
    EXPECT_EQ(s.is_empty(), true);
}

TEST(Queue, item_pop_makes_queue_empty)
{
    TQueue<int> s(5);
    s.push(1);
    int number = s.pop();
    EXPECT_EQ(s.is_empty(), true);
}

TEST(Queue, queue_with_items_is_not_empty)
{
    TQueue<int> s(5);
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(s.is_empty(), false);
}

TEST(Queue, item_push_makes_queue_full)
{
    TQueue<int> s(3);
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(s.is_full(), true);
}

TEST(Queue, cant_add_item_to_full_queue)
{
    TQueue<int> s(3);
    s.push(1);
    s.push(2);
    s.push(3);
    ASSERT_ANY_THROW(s.push(4));
}

TEST(Queue, cant_pop_item_from_empty_queue)
{
    TQueue<int> s(1);
    s.push(1);
    s.pop();
    ASSERT_ANY_THROW(s.pop());
}

TEST(Queue, can_get_max_element)
{
    TQueue<int> s(3);
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(s.get_max(), 3);
}

TEST(Queue, can_get_least_element)
{
    TQueue<int> s(3);
    s.push(1);
    s.push(2);
    s.push(3);
    EXPECT_EQ(s.get_least(), 1);
}
