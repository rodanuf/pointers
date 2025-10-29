#include <gtest/gtest.h>
#include "uniq_ptr.hpp"

TEST(uniq_ptr_test, constructor_from_pointer_test)
{
    int *p = new int(5);
    uniq_ptr<int> ptr = make_uniq_from(p);
    ASSERT_EQ(*ptr, 5);
}

TEST(uniq_ptr_test, constructor_from_nullptr_test)
{
    int *p = nullptr;
    uniq_ptr<int> ptr = make_uniq_from(p);
    ASSERT_EQ(ptr.get(), nullptr);
}

TEST(uniq_ptr_test, move_constructor)
{
    int *p = new int(5);
    uniq_ptr<int> ptr = make_uniq_from(p);
    uniq_ptr<int> ptr2(std::move(ptr));
    ASSERT_EQ(*ptr2, 5);
}

TEST(uniq_ptr_test, get_method_test)
{
    int *p = new int(5);
    uniq_ptr<int> ptr = make_uniq_from(p);
    auto new_p = ptr.get();
    ASSERT_EQ(*new_p, 5);
}

TEST(uniq_ptr_test, release_method_test)
{
    int *p = new int(5);
    uniq_ptr<int> ptr = make_uniq_from(p);
    auto new_p = ptr.release();
    ASSERT_EQ(ptr.get(), nullptr);
    ASSERT_EQ(*new_p, 5);
}

TEST(uniq_ptr_test, reset_method_test)
{
    int *p = new int(5);
    uniq_ptr<int> ptr = make_uniq_from(p);
    int *p2 = new int(10);
    ptr.reset(p2);
    ASSERT_EQ(ptr.get(), p2);
    ASSERT_EQ(*ptr, 10);
}

TEST(uniq_ptr_test, swap_method_test)
{
    int *p = new int(5);
    int *p2 = new int(10);
    uniq_ptr<int> ptr = make_uniq_from(p);
    uniq_ptr<int> ptr2 = make_uniq_from(p2);
    ptr.swap(ptr2);
    ASSERT_EQ(*ptr, 10);
    ASSERT_EQ(*ptr2, 5);
}

TEST(uniq_ptr_test, clear_method_test)
{
    int *p = new int(5);
    uniq_ptr<int> ptr = make_uniq_from(p);
    ptr.clear();
    ASSERT_EQ(ptr.get(), nullptr);
}

TEST(uniq_ptr_test, move_constructor_test)
{
    int *p = new int(5);
    uniq_ptr<int> ptr = make_uniq_from(p);
    ASSERT_EQ(*ptr, 5);
}

TEST(uniq_ptr_test, constructor_from_object_test)
{
    int a = 5;
    auto ptr = make_uniq_from(a);
    ASSERT_EQ(*ptr, 5);
}
