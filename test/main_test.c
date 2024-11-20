#include <stdbool.h>

#include <unity.h>

#include <common.h>
#include <Allocator.h>

void 
setUp(void) {

}

void
tearDown(void) {

}

void
test_arena_alloc(void) {
	TEST_ASSERT_EQUAL(42, 42);
}

int
main(void) {
	UNITY_BEGIN();
	RUN_TEST(test_arena_alloc);
	return UNITY_END();
}

