#include "gmock/gmock.h"
#include "calc.cpp"

TEST(Group, TC1) {
	Cal cal;

	int ret = cal.getSum(10, 20);

	EXPECT_EQ(30, ret);
}