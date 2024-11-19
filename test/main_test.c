#include <common.h>
#include <rktest/rktest.h>

u8 factorial(u8 n) {
	u8 result = 1;
	for (u8 i = 1; i <= n; i++) {
		result *= i;
	}

	return result;
}

TEST(simple_tests, factorial_of_negative_is_one) {
	EXPECT_EQ(factorial(-1), 1);
	EXPECT_EQ(factorial(-42), 1);
}

TEST(simple_tests, factorial_of_zero_is_one) {
	EXPECT_EQ(factorial(0), 1);
}

TEST(simple_tests, factorial_of_positive_numbers) {
	EXPECT_EQ(factorial(3), 6);
	EXPECT_EQ(factorial(4), 24);
}