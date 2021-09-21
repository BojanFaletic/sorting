#include <gtest/gtest.h>
#include "algorithms.hpp"
#include <array>

TEST(selection, sort)
{
    std::array<int, 3> vv{3, 1, 2};
    selection(vv);

    std::array<int, 3> correct_vv{1, 2, 3};
    EXPECT_EQ(vv, correct_vv);
}

TEST(selection, swap){
    std::array<int, 2> v{1,2};
    swap(v[0], v[1]);

    std::array<int, 2> v_correct{2, 1};
    EXPECT_EQ(v, v_correct);
}


TEST(bubble, sort)
{
    std::array<int, 3> vv{3, 1, 2};
    bubble(vv);

    std::array<int, 3> correct_vv{1, 2, 3};
    EXPECT_EQ(vv, correct_vv);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}