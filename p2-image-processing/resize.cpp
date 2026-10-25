#include <iostream>
#include <fstream>
#include <string>

#include "Image.hpp"
#include "processing.hpp"
using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 4 && argc != 5) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
  }

  string in_filename = argv[1];
  string out_filename = argv[2];

  ifstream fin(in_filename);
  if (!fin.is_open()) {
    cout << "Error opening file: " << in_filename << endl;
    return 1;
  }

  Image *img = new Image;
  Image_init(img, fin);
  fin.close();

  int target_width = atoi(argv[3]);
  int target_height = (argc == 5) ? atoi(argv[4]) : Image_height(img);

  if (target_width <= 0 || target_width > Image_width(img) ||
      target_height <= 0 || target_height > Image_height(img)) {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    delete img;
    return 1;
  }

  seam_carve(img, target_width, target_height);

  ofstream fout(out_filename);
  if (!fout.is_open()) {
    cout << "Error opening file: " << out_filename << endl;
    delete img;
    return 1;
  }

  Image_print(img, fout);
  fout.close();

  delete img;
  return 0;
}