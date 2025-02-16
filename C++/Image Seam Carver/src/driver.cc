#include "image_processing.hpp"

using namespace std;

// Helper Functions
Image openImage(string image_name, int image_width, int image_height) {

  ifstream img(image_name);

  if (!img.is_open()) {
    cout << "File could not be opened." << endl;
    exit(0);
  }

  Image toReturn(image_name);

  if (image_width > toReturn.Width()) {
    cout << "Width is too big. We cannot currently grow the image." << endl;
    exit(0);
  }

  if (image_height > toReturn.Height()) {
    cout << "Height is too big. We cannot currently grow the image." << endl;
    exit(0);
  }

  return toReturn;

}

void reduceWidth(Image& img, int new_width) {

  int times = img.Width() - new_width;
  vector <int> seam;

  for (int i = 0; i < times; i++) {
    seam = FindVerticalSeam(img);
    RemoveVerticalSeam(img, seam);
  }

}

void reduceHeight(Image& img, int new_height) {

  RotateLeft(img);
  reduceWidth(img, new_height);
  RotateRight(img);

}

void createNewPPM(Image& img, string file_name, int new_width, int new_height) {

  string img_name;
  for (int i = 0; i < file_name.length(); i++) {
    if (file_name[i] == '.') {
      break;
    }
    img_name += file_name[i];
    if (file_name[i] == '/') {
      img_name = "";
    }
  }

  string new_name = img_name + to_string(new_width) + "x" + to_string(new_height) + "_actual.ppm";
  ofstream fout(new_name);

  fout << "P3" << endl << new_width << " " << new_height << endl << "255" << endl;

  for (int row = 0; row < new_height; row++) {
    for (int col = 0; col < new_width; col++) {
      fout << img.GetPixel(row, col).r << " ";
      fout << img.GetPixel(row, col).g << " ";
      fout << img.GetPixel(row, col).b << " ";
    }
    fout << endl;
  }

  fout.close();

}

int main(int argc, char* argv[]) {
  // MP PART: 3

  if (argc != 4) {
    cout << "The format is, <image_name> <new_width> <new_height>" << endl;
    return 0;
  }

  string image_name = argv[1];
  int new_width = stoi(argv[2]);
  int new_height = stoi(argv[3]);
  Image img = openImage(image_name, new_width, new_height);

  reduceWidth(img, new_width);
  reduceHeight(img, new_height);

  createNewPPM(img, image_name, new_width, new_height);

}