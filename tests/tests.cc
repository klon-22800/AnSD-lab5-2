#include <gtest/gtest.h>
#include <hash_table/hash_table.h>

using namespace std;
using namespace hash_table;

TEST(Functions_test, sum_test) {
    int a = 5;
    int b = 5;
    int c = sum(a, b);
    EXPECT_EQ(c, 10);
}