#include <gtest/gtest.h>
#include "shared_ptr.hpp"

TEST(shared_ptr_test, constructor_from_pointer_test)
{
    int *p = new int(5);
    shared_ptr<int> ptr(p);
    EXPECT_EQ(*ptr, 5);
    EXPECT_EQ(ptr.use_count(), 1);
}

TEST(shared_ptr_test, copy_constructor_test)
{
    int *p = new int(5);
    shared_ptr<int> ptr1(p);
    shared_ptr<int> ptr2(ptr1);
    EXPECT_EQ(*ptr2, 5);
    EXPECT_EQ(ptr2.use_count(), 2);
}

TEST(shared_ptr_test, move_constructor_test)
{
    int *p = new int(5);
    shared_ptr<int> ptr1(p);
    shared_ptr<int> ptr2(std::move(ptr1));
    EXPECT_EQ(*ptr2, 5);
    EXPECT_EQ(ptr2.use_count(), 1);
}

TEST(shared_ptr_test, move_constructor_from_uniq)
{
    int *p = new int(5);
    uniq_ptr<int> ptr1 = make_uniq_from(p);  
    shared_ptr<int> ptr2(std::move(ptr1));
    EXPECT_EQ(*ptr2, 5);
    EXPECT_EQ(ptr2.use_count(), 1);
    EXPECT_EQ(ptr1.get(), nullptr);
}

TEST(shared_ptr_test, copy_assignment_test)
{
    int *p = new int(5);
    shared_ptr<int> ptr1(p);
    shared_ptr<int> ptr2 = ptr1;
    EXPECT_EQ(*ptr2, 5);
    EXPECT_EQ(ptr2.use_count(), 2);
}

TEST(shared_ptr_test, move_assignment_test)
{
    int *p = new int(5);
    shared_ptr<int> ptr1(p);
    shared_ptr<int> ptr2 = std::move(ptr1);
    EXPECT_EQ(*ptr2, 5);
    EXPECT_EQ(ptr2.use_count(), 1);
}

TEST(shared_ptr_test, check_unique)
{
    int *p = new int(5);
    shared_ptr<int> ptr1(p);
    shared_ptr<int> ptr2 = ptr1;
    EXPECT_EQ(ptr1.use_count(), 2);
    EXPECT_EQ(ptr2.use_count(), 2);
    EXPECT_EQ(ptr1.is_unique(), false);
}

TEST(shared_ptr_test, reset_test)
{
    int *p = new int(5);
    shared_ptr<int> ptr1(p);
    shared_ptr<int> ptr2 = ptr1;
    EXPECT_EQ(ptr1.use_count(), 2);
    int *p2 = new int(10);
    ptr1.reset(p2);
    EXPECT_EQ(*(ptr1.get()), 10);
    EXPECT_EQ(ptr1.use_count(), 1);
}

TEST(shared_ptr_test, swap_test)
{
    int *p = new int(5);
    int *p2 = new int(10);
    shared_ptr<int> ptr1(p);
    shared_ptr<int> ptr2(p2);
    shared_ptr<int> ptr3 = ptr1;
    ptr1.swap(ptr2);
    EXPECT_EQ(*(ptr1.get()), 10);
    EXPECT_EQ(ptr1.use_count(), 1);
}