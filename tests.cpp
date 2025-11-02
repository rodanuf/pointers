#include <gtest/gtest.h>
#include "test_uniq_ptr.cpp"
#include "test_shared_ptr.cpp"

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::GTEST_FLAG(color) = 1;
    return RUN_ALL_TESTS();
}