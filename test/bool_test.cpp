#include <gtest/gtest.h>

TEST(bool_test, TrueEqTrue) {
    EXPECT_EQ(true, true) << "true equals true";
}
