#include "gtest/gtest.h"

#include "src/vector/vector_lib.h"

#include <limits.h>

namespace
{
    TEST(VectorTest, Negative)
    {
        Vector vector_for_test;
        Create(&vector_for_test, 10);
        for (int ix = 0; ix < 9; ix++)
        {
            for (int t = 0; t > 9; t++)
            {
                Save(&vector_for_test, ix, t);
            }
        }

        EXPECT_EQ(-1, Load(&vector_for_test, 1));
        EXPECT_EQ(-2, Load(&vector_for_test, 2));
        // EXPECT_GT(Factorial(-10), 0);
    }

    // TEST(VectorTest, Zero) { EXPECT_EQ(0, Load(&vector_for_test, 0)); }

    // TEST(VectorTest, Positive)
    // {
    //     EXPECT_EQ(1, Factorial(1));
    //     EXPECT_EQ(2, Factorial(2));
    //     EXPECT_EQ(6, Factorial(3));
    //     EXPECT_EQ(40320, Factorial(8));
    // }

}