#include <stdbool.h>

#include <unity.h>

#include <common.h>
#include <allocator/allocator.h>

#define ARENA_SIZE 1024

static u8 test_memory[ARENA_SIZE];
static Arena arena;
static Allocator arena_allocator;

void setUp(void) {
    // Initialize the arena and allocator before each test
    arena = arena_init(test_memory, ARENA_SIZE);
    arena_allocator = arena_alloc_init(&arena);

    TEST_ASSERT_NOT_NULL(arena.base);
    TEST_ASSERT_EQUAL_UINT(ARENA_SIZE, arena.size);
    TEST_ASSERT_EQUAL_UINT(0, arena.offset);
    TEST_ASSERT_EQUAL_UINT(0, arena.committed);
}

void tearDown(void) {
    // No specific cleanup is required in this setup
}

// Test that initialization works
void test_Arena_Init(void) {
    TEST_ASSERT_EQUAL_PTR(test_memory, arena.base);
    TEST_ASSERT_EQUAL_UINT(ARENA_SIZE, arena.size);
    TEST_ASSERT_EQUAL_UINT(0, arena.offset);
    TEST_ASSERT_EQUAL_UINT(0, arena.committed);
}

// Test allocation within capacity
void test_Arena_Allocate_WithinCapacity(void) {
    void* ptr1 = arena_alloc_aligned(&arena, 256, DEFAULT_ALIGNMENT);
    TEST_ASSERT_NOT_NULL(ptr1);
    TEST_ASSERT_EQUAL_UINT(256, arena.offset);

    void* ptr2 = arena_alloc_aligned(&arena, 512, DEFAULT_ALIGNMENT);
    TEST_ASSERT_NOT_NULL(ptr2);
    TEST_ASSERT_EQUAL_UINT(768, arena.offset);
}

// Test allocation exceeding capacity
void test_Arena_Allocate_ExceedingCapacity(void) {
    void* ptr1 = arena_alloc_aligned(&arena, ARENA_SIZE + 1, DEFAULT_ALIGNMENT);
    TEST_ASSERT_NULL(ptr1);
    TEST_ASSERT_EQUAL_UINT(0, arena.offset);

    void* ptr2 = arena_alloc_aligned(&arena, ARENA_SIZE, DEFAULT_ALIGNMENT);
    TEST_ASSERT_NOT_NULL(ptr2);
    TEST_ASSERT_EQUAL_UINT(ARENA_SIZE, arena.offset);

    void* ptr3 = arena_alloc_aligned(&arena, 1, DEFAULT_ALIGNMENT); // No more space left
    TEST_ASSERT_NULL(ptr3);
}

// Test resetting the arena
void test_Arena_Reset(void) {
    void* ptr1 = arena_alloc_aligned(&arena, 512, DEFAULT_ALIGNMENT);
    TEST_ASSERT_NOT_NULL(ptr1);
    TEST_ASSERT_EQUAL_UINT(512, arena.offset);

    arena_free_all(&arena);
    TEST_ASSERT_EQUAL_UINT(0, arena.offset);
    TEST_ASSERT_EQUAL_UINT(0, arena.committed);
}

// Test alignment
void test_Arena_Alignment(void) {
    void* ptr1 = arena_alloc_aligned(&arena, 3, 8); // Allocate 3 bytes with 8-byte alignment
    TEST_ASSERT_NOT_NULL(ptr1);
    TEST_ASSERT_EQUAL_PTR((void*)align_forward((usize)test_memory, 8), ptr1);

    void* ptr2 = arena_alloc_aligned(&arena, 5, 16); // Allocate 5 bytes with 16-byte alignment
    TEST_ASSERT_NOT_NULL(ptr2);
    TEST_ASSERT_EQUAL_PTR((void*)align_forward((usize)test_memory + 8 + 3, 16), ptr2);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_Arena_Init);
    RUN_TEST(test_Arena_Allocate_WithinCapacity);
    RUN_TEST(test_Arena_Allocate_ExceedingCapacity);
    RUN_TEST(test_Arena_Reset);
    RUN_TEST(test_Arena_Alignment);

    return UNITY_END();
}
