#include <cassert>
#include <vector>
#include <algorithm>
#include "Matrix.hpp"
#include "processing.hpp"

using namespace std;

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}


// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}

static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}


// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  // assert(false);
  int diff2, maxx = 0;
  Matrix_init(energy, Image_width(img), Image_height(img));
  for (int i = 1; i < Image_height(img) - 1; i++) {
    for (int j = 1; j < Image_width(img) - 1; j++) {
      diff2 = squared_difference((Image_get_pixel(img, i - 1, j)),
                                 Image_get_pixel(img, i + 1, j));
      diff2 += squared_difference((Image_get_pixel(img, i, j - 1)),
                                  Image_get_pixel(img, i, j + 1));
      *Matrix_at(energy, i, j) = diff2;
      maxx = std::max(maxx, diff2);
    }
  }
  for (int i = 0; i < Image_height(img); i++) {
    for (int j = 0; j < Image_width(img); j++) {
      if (i == 0 || j == 0 || i == Image_height(img) - 1 ||
          j == Image_width(img) - 1) {
        *Matrix_at(energy, i, j) = maxx;
      }
    }
  }
}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  Matrix_init(cost, Matrix_width(energy), Matrix_height(energy));
  for (int i = 0; i < Matrix_width(energy); i++) {
    *Matrix_at(cost, 0, i) = *Matrix_at(energy, 0, i);
  }
  for (int i = 1; i < Matrix_height(energy); i++) {
    for (int j = 0; j < Matrix_width(energy); j++) {
      // *Matrix_at(cost, i, j) = *Matrix_at(energy, i, j) +
      // Matrix_min_value_in_row(cost, i - 1, (j != 0) ? j - 1 : j, (j !=
      // Matrix_width(energy) - 1) ? j + 2 : j + 1); // column_end -> exclusive
      int start_col = (j == 0) ? 0 : j - 1;
      int end_col = (j == Matrix_width(energy) - 1) ? Matrix_width(energy) : j + 2;

      *Matrix_at(cost, i, j) = *Matrix_at(energy, i, j);
      int min_above = Matrix_min_value_in_row(cost, i - 1, start_col, end_col);
      *Matrix_at(cost, i, j) += min_above; 
    }
  }
}


// REQUIRES: cost points to a valid Matrix
// EFFECTS:  Returns the vertical seam with the minimal cost according to the given
//           cost matrix, represented as a vector filled with the column numbers for
//           each pixel along the seam, with index 0 representing the lowest numbered
//           row (top of image). The length of the returned vector is equal to
//           Matrix_height(cost).
//           While determining the seam, if any pixels tie for lowest cost, the
//           leftmost one (i.e. with the lowest column number) is used.
//           See the project spec for details on computing the minimal seam.
//           Note: When implementing the algorithm, compute the seam starting at the
//           bottom row and work your way up.
vector<int> find_minimal_vertical_seam(const Matrix *cost) {
  vector<int> seam;
  int h = Matrix_height(cost);
  int w = Matrix_width(cost);
  int now = Matrix_column_of_min_value_in_row(cost, h - 1, 0, w);

  seam.push_back(now);
  for (int i = Matrix_height(cost) - 2; i >= 0; i--) {
    // now = Matrix_column_of_min_value_in_row(cost, i, (now != 0) ? now - 1 :
    // now, (now != Matrix_width(cost) - 1) ? now + 2 : now + 1);   //
    // column_end -> exclusive
    int start_col = (now == 0) ? 0 : now - 1;
    int end_col = (now == w - 1) ? w : now + 2;
    
    now = Matrix_column_of_min_value_in_row(cost, i, start_col, end_col);
    seam.push_back(now);
  }
  std::reverse(seam.begin(), seam.end());
  return seam;
}


// REQUIRES: img points to a valid Image with width >= 2
//           seam.size() == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Declare a new variable to hold the smaller Image, and
//           then do an assignment at the end to copy it back into the
//           original image.
void remove_vertical_seam(Image *img, const vector<int> &seam) {
  Image newImg;
  Image_init(&newImg, Image_width(img) - 1, Image_height(img));
  for (int i = 0; i < Image_height(img); i++) {
    int cnt = 0;
    for (int j = 0; j < Image_width(img); j++) {
      if (seam[i] == j) {
        continue;
      }
      Image_set_pixel(&newImg, i, cnt, Image_get_pixel(img, i, j));
      cnt++;
    }
  }
  *img = newImg;
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
void seam_carve_width(Image *img, int newWidth) {
  Matrix energy;
  Matrix cost;
  int nowWidth = Image_width(img);
  for (int i = 0; i < nowWidth - newWidth; i++) {
    compute_energy_matrix(img, &energy);
    compute_vertical_cost_matrix(&energy, &cost);
    remove_vertical_seam(img, find_minimal_vertical_seam(&cost));
  }
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
  rotate_left(img);
  seam_carve_width(img, newHeight);
  rotate_right(img);
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
  seam_carve_width(img, newWidth);
  seam_carve_height(img, newHeight);
}
