#include <vector>
#include "tutorial.hpp"
#include "unit_test_framework.hpp"

using namespace std;
// We define a test case with the TEST(<test_name>) macro.
// <test_name> can be any valid C++ function name.
TEST(true_is_true) {
  ASSERT_TRUE(true);
}

TEST(numbers_are_equal) { ASSERT_EQUAL(42, 42); }

TEST(add_basic) {
  ASSERT_EQUAL(add(2, 2), 4);
  ASSERT_EQUAL(add(2, 3), 5);
  ASSERT_EQUAL(add(5, 0), 5);
  ASSERT_EQUAL(add(0, 0), 0);
}

TEST(add_negative) {
  ASSERT_EQUAL(add(2, -2), 0);
  ASSERT_EQUAL(add(3, -5), -2);
  ASSERT_EQUAL(add(-3, 5), 2);
  ASSERT_EQUAL(add(-5, -5), -10);
}

TEST(add_floating_point) {
  ASSERT_ALMOST_EQUAL(add(0.1, 0.2), 0.3, 0.001);
  ASSERT_ALMOST_EQUAL(add(0.1, 0.1), 0.2, 0.001);
  ASSERT_ALMOST_EQUAL(add(0.1, -0.1), 0.0, 0.001);
  ASSERT_ALMOST_EQUAL(add(-0.1, -0.1), -0.2, 0.001);
}

TEST(test_slide_right_1) {
  vector<int> v = { 4, 0, 1, 3, 3 };
  vector<int> expected = { 3, 4, 0, 1, 3 };
  slideRight(v);
  ASSERT_SEQUENCE_EQUAL(v, expected);
}

TEST(test_flip_1) {
  vector<int> v = { 4, 0, 1, 3, 3 };
  vector<int> expected = { 3, 3, 1, 0, 4 };
  flip(v);
  ASSERT_SEQUENCE_EQUAL(v, expected);
}

TEST(test_flip_2) {
  vector<int> v = { 5, 3, 2, 3, 3 };
  vector<int> expected = { 3, 4, 0, 0, 4 };
  flip(v);
  ASSERT_SEQUENCE_EQUAL(v, expected);
}


TEST_MAIN() // No semicolon!

