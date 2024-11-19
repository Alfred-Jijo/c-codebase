#include <common.h>
#include <stdbool.h>
#include <unity/unity.h>

void 
setUp() {

}

void
tearDown() {

}

void
test_func(void) {
	TEST_ASSERT( 1 == 1);
}

int
main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_func);
	return UNITY_END();
}

