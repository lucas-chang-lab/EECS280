#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}

TEST(test_matrix_min_value) {
  Matrix mat;
  Matrix_init(&mat, 7, 2);

  ASSERT_EQUAL(Matrix_width(&mat), 7);
  ASSERT_EQUAL(Matrix_height(&mat), 2);

  Matrix_fill(&mat, 8);

  int *ptr = Matrix_at(&mat, 1, 0);
  ASSERT_EQUAL(*ptr, 8);
  *ptr = 100;

  const int *cptr = Matrix_at(&mat, 1, 0);
  ASSERT_EQUAL(*cptr, 100);

  Matrix_fill_border(&mat, 3);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 3);

  ASSERT_EQUAL(Matrix_max(&mat), 3);

  *ptr = -10;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 1, 0, 6), 0);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0, 6), -10);
}

TEST(test_matrix_print) {
  Matrix mat;
  Matrix_init(&mat, 3, 3);

  *Matrix_at(&mat, 1, 1) = 50;
  ostringstream expected;
  expected << "3 3\n"
           << "0 0 0 \n"
           << "0 50 0 \n"
           << "0 0 0 \n";
  ostringstream actual;
  Matrix_print(&mat, actual);
  ASSERT_EQUAL(expected.str(), actual.str());
}

TEST(test_matrix_min_value_tie_breaking) {
  Matrix mat;
  Matrix_init(&mat, 4, 1);
  *Matrix_at(&mat, 0, 0) = 10;
  *Matrix_at(&mat, 0, 1) = 5;  // Leftmost minimum
  *Matrix_at(&mat, 0, 2) = 5;  // Tied minimum
  *Matrix_at(&mat, 0, 3) = 20;

  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 0, 4), 1);
}

TEST(test_matrix_one_by_one_bounds) {
  Matrix mat;
  Matrix_init(&mat, 1, 1);
  *Matrix_at(&mat, 0, 0) = 99;
  
  ASSERT_EQUAL(Matrix_max(&mat), 99);
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 0, 1), 99);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 0, 1), 0);
  
  Matrix_fill_border(&mat, 7);
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 7);
}

TEST(test_matrix_sub_region_min_and_tie) {
  Matrix mat;
  Matrix_init(&mat, 6, 1);
  
  *Matrix_at(&mat, 0, 0) = 1;
  *Matrix_at(&mat, 0, 1) = 99; 
  *Matrix_at(&mat, 0, 2) = 10; // Leftmost minimum inside sub-region [1, 5)
  *Matrix_at(&mat, 0, 3) = 10; // Tied minimum inside sub-region [1, 5)
  *Matrix_at(&mat, 0, 4) = 50;
  *Matrix_at(&mat, 0, 5) = 2;  // Absolute minimum, outside sub-region

  // search column indices 1, 2, 3, 4
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 0, 1, 5), 10);
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 1, 5), 2);
}

TEST_MAIN() // Do NOT put a semicolon here
