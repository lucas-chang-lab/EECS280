#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}


TEST(test_Image_istream_basic) {
  Image img1;
  string input = "P3 2 2\t255 255 0 0\n0\n255 0 \n0 0 255 255 255 255 \n";
  std::istringstream ss_input(input);
  Image_init(&img1, ss_input);

  Image img2;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img2, 2, 2);
  Image_set_pixel(&img2, 0, 0, red);
  Image_set_pixel(&img2, 0, 1, green);
  Image_set_pixel(&img2, 1, 0, blue);
  Image_set_pixel(&img2, 1, 1, white);

  ASSERT_TRUE(Image_equal(&img1, &img2));
}

TEST(test_image_getters) {
  Image img;
  Image_init(&img, 4, 7);
  
  ASSERT_EQUAL(Image_width(&img), 4);
  ASSERT_EQUAL(Image_height(&img), 7);

  Pixel target_color = {20, 30, 40};
  Image_set_pixel(&img, 5, 2, target_color);

  Pixel retrieved = Image_get_pixel(&img, 5, 2);
  ASSERT_EQUAL(retrieved.r, 20);
  ASSERT_EQUAL(retrieved.g, 30);
  ASSERT_EQUAL(retrieved.b, 40);
}

TEST(test_image_fill) {
  Image img;
  Image_init(&img, 3, 5);
  Pixel custom_color = {10, 20, 30};
  Image_fill(&img, custom_color);

  for (int r = 0; r < 5; ++r) {
    for (int c = 0; c < 3; ++c) {
      Pixel p = Image_get_pixel(&img, r, c);
      ASSERT_EQUAL(p.r, 10);
      ASSERT_EQUAL(p.g, 20);
      ASSERT_EQUAL(p.b, 30);
    }
  }
}

TEST(test_image_stream_excess_whitespace) {
  std::stringstream ss;
  ss << "P3\n1 2\n255\n"
     << "10 20 30\n"
     << "40 50 60\n\n  \n\t\n"; // Trailing noise entries

  Image img;
  Image_init(&img, ss);
  ASSERT_EQUAL(Image_width(&img), 1);
  ASSERT_EQUAL(Image_height(&img), 2);
  
  Pixel second_row = Image_get_pixel(&img, 1, 0);
  ASSERT_EQUAL(second_row.r, 40);
  ASSERT_EQUAL(second_row.g, 50);
  ASSERT_EQUAL(second_row.b, 60);
}

TEST_MAIN() // Do NOT put a semicolon here
