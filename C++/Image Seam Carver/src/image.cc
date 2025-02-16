#include "image.hpp"
using namespace std;

// Write the member functions of Image below.

// REQUIRES: height and width are > 0.
// MODIFIES: Image
// EFFECTS: Initializes an image of height x width.
// MP PART: 1
Image::Image(int height, int width) {
  vector<Pixel> w(width);
  for (int i = 0; i < height; i++) {
    data_.push_back(w);
  }
}

// REQUIRES: filename leads to a valid PPM P3 file.
// MODIFIES: Image
// EFFECTS: Initializes an image from a PPM file at filename.
//          If the file cannot be opened, throw a runtime_error exception with
//          the message "File could not be opened."
// MP PART: 1
Image::Image(const std::string& filename) {
  ifstream fin(filename);

  if (!fin.is_open()) {
    throw runtime_error("File could not be opened.");
  }

  string p3;
  fin >> p3;

  int width;
  int height;
  fin >> width;
  fin >> height;

  int max_rgb;
  fin >> max_rgb;

  Pixel p;
  for (int i = 0; i < height; i++) {
    data_.push_back({});
    for (int j = 0; j < width; j++) {
      fin >> p.r;
      fin >> p.g;
      fin >> p.b;
      data_[i].push_back(p);
    }
  }
}

// REQUIRES:
// MODIFIES:
// EFFECTS: Writes the image to a PPM file named filename.
//          The three header items in the PPM file are not followed by a space,
//          just a newline. Each pixel is printed in the format of "<red>
//          <green> <blue> ". This includes the last pixel in the row. Each row
//          is followed by a newline.
// MP PART: 1
void Image::SaveToFile(const std::string& filename) {
  ofstream fout(filename);

  fout << "P3" << endl;
  fout << data_[0].size() << " " << data_.size() << endl;
  fout << "255" << endl;

  for (const auto& row : data_) {
    for (const Pixel& column : row) {
      fout << column.r << " " << column.g << " " << column.b << " ";
    }
    fout << endl;
  }
}

// REQUIRES: data_ has at least 1 row.
// MODIFIES:
// EFFECTS: Returns the width of the 1st row of the image as an int.
//          Use assert to check the REQUIRES.
// MP PART: 1
int Image::Width() const {
  assert(data_.size() > 0);
  return data_[0].size();
}

// REQUIRES:
// MODIFIES:
// EFFECTS: Returns the image height as an int.
// MP PART: 1
int Image::Height() const { return data_.size(); }

// REQUIRES: row is between [0, height), and col is between [0, width).
// MODIFIES:
// EFFECTS: Returns the pixel at row, col.
//          Use assert to check the REQUIRES.
// MP PART: 1
Pixel Image::GetPixel(int row, int col) const {
  assert(row >= 0 && row < data_.size());
  assert(col >= 0 && col < data_[row].size());
  return data_[row][col];
}

// REQUIRES: row is between [0, height), col is between [0, width), and
//           new_pixel is a valid pixel.
// MODIFIES: Image
// EFFECTS: Sets the pixel at row, col to new_pixel.
//          Use assert to check the REQUIRES.
// MP PART: 1
void Image::SetPixel(int row, int col, Pixel new_pixel) {
  assert(row >= 0 && row < data_.size());
  assert(col >= 0 && col < data_[0].size());
  assert(new_pixel.r >= 0 && new_pixel.r < 256);
  assert(new_pixel.g >= 0 && new_pixel.g < 256);
  assert(new_pixel.b >= 0 && new_pixel.b < 256);

  data_[row][col].r = new_pixel.r;
  data_[row][col].g = new_pixel.g;
  data_[row][col].b = new_pixel.b;
}

// REQUIRES: row is between [0, height), col is between [0, width). There are
//            at least 2 pixels in row's corresponding row.
// MODIFIES: Image
// EFFECTS: Removes the pixel at row, col. Changing that row to have one less
//          pixel. Use assert to check the requires.
//          hint: Feel free to use any vector member functions
// MP PART: 1
void Image::RemovePixel(int row, int col) {
  assert(row >= 0 && row < data_.size());
  assert(col >= 0 && col < data_[row].size());
  assert(data_[row].size() > 1);

  data_[row].erase(data_[row].begin() + col);
}

// private: vector<vector<Pixel>> data_;