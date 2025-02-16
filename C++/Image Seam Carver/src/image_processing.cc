#include "image_processing.hpp"
using namespace std;

// Write the functions from image_processing below.

// REQUIRES:
// MODIFIES: image_
// EFFECTS: Rotates the image 90 degrees counterclockwise.
/*
image_ 
A B C D
E F G H
I J K L

would become
D H L
C G K
B F J 
A E I
*/
// MP PART: 1
void RotateLeft(Image& image_) {

    int new_height = image_.Width();
    int new_width = image_.Height();

    Image new_image = Image(new_height, new_width);

    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            new_image.SetPixel(i, j, image_.GetPixel(j, (new_height-1) - i));
        }
    }

    image_ = new_image;

}

// REQUIRES:
// MODIFIES: image_
// EFFECTS: Rotates the image 90 degrees clockwise.
//          hint: You can use other image_processing functions
/*
image_ 
D H L
C G K
B F J
A E I

would become
A B C D
E F G H
I J K L
*/
// MP PART: 1
void RotateRight(Image& image_) {

    int new_height = image_.Width();
    int new_width = image_.Height();

    Image new_image = Image(new_height, new_width);

    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            new_image.SetPixel(i, j, image_.GetPixel((new_width-1) - j, i));
        }
    }

    image_ = new_image;

}

// REQUIRES: image_ is a rectangle of pixels.
// MODIFIES:
// EFFECTS: Returns the energy matrix for image_. See spec for algorithm.
//          hint: use SquaredPixelEnergy() from pixel.hpp
//          hint: use kHighEnergy
// MP PART: 2
vector<vector<int>> CalculateEnergy(const Image& image_) {

    vector<vector<int>> energy;

    for (int i = 0; i < image_.Height(); i++) {
        energy.push_back({});
        for (int j = 0; j < image_.Width(); j++) {
            energy[i].push_back(0);
        }
    }

    for (int i = 0; i < image_.Height(); i++) {
        for (int j = 0; j < image_.Width(); j++) {
            if (i == 0 || j == 0 || i == image_.Height()-1 || j == image_.Width()-1) {
                energy[i][j] = kHighEnergy;
            } else {
                Pixel north_pixel = image_.GetPixel(i-1, j);
                Pixel south_pixel = image_.GetPixel(i+1, j);
                Pixel west_pixel = image_.GetPixel(i, j-1);
                Pixel east_pixel = image_.GetPixel(i, j+1);
                int squared_energy = SquaredPixelEnergy(north_pixel, south_pixel) + SquaredPixelEnergy(west_pixel, east_pixel);
                energy[i][j] = squared_energy;
            }
        }
    }

    return energy;

}

// REQUIRES: energy is a rectangle.
// MODIFIES:
// EFFECTS: Returns the vertical cost matrix for energy. See spec for the algorithm.
// MP PART: 2
vector<vector<int>> CalculateCostVertical(const vector<vector<int>>& energy) {

    vector<vector<int>> cost;

    for (int i = 0; i < energy.size(); i++) {
        cost.push_back({});
        for (int j = 0; j < energy[i].size(); j++) {
            cost[i].push_back(0);
        }
    }

    int min_val;
    for (int i = 0; i < cost.size(); i++) {
        for (int j = 0; j < cost[i].size(); j++) {
            if (i == 0) {
                min_val = 0;
            } else if (j == 0) {
                min_val = min(cost[i-1][j], cost[i-1][j+1]);
            } else if (j == cost[i].size()-1) {
                min_val = min(cost[i-1][j-1], cost[i-1][j]);
            } else {
                min_val = min(min(cost[i-1][j-1], cost[i-1][j]), cost[i-1][j+1]);
            }
            cost[i][j] = energy[i][j] + min_val;
        }
    }

    return cost;

}

// REQUIRES: image_ is a rectangle of pixels.
// MODIFIES:
// EFFECTS: Returns the lowest energy vertical seam in the image. The returned
//          vector's size is image_ height. Each element in the vector is
//          between [0, image_ width). The value at the 0th index indicates the
//          column value of the seam at row 0 and so forth. See spec for the
//          algorithm. hint: You will need to call CalculateEnergy, and
//          CalculateCostVertical.
// MP PART: 2
vector<int> FindVerticalSeam(const Image& image_) {

    vector<vector<int>> energy = CalculateEnergy(image_);
    vector<vector<int>> cost = CalculateCostVertical(energy);
    vector<int> seam(cost.size());
    
    //first, find starting point of seam
    int last_row = image_.Height()-1;
    int min_val = 9999999;
    for (int i = 0; i < cost[last_row].size(); i++) {
        if (cost[last_row][i] < min_val) {
            min_val = cost[last_row][i];
            seam[last_row] = i;
        }
    }

    //find rest of the seam
    for (int row = last_row-1; row >= 0; row--) {
        //if it's at the left border
        int prev_col = seam[row+1];
        if (prev_col == 0) {
            if (cost[row][prev_col] <= cost[row][prev_col+1]) {
                seam[row] = prev_col;
            } else {
                seam[row] = prev_col + 1;
            }
        } else if (prev_col == cost[row].size()-1) { //if it's at the right border
            if (cost[row][prev_col-1] <= cost[row][prev_col]) {
                seam[row] = prev_col - 1;
            } else {
                seam[row] = prev_col;
            }
        } else { //anywhere in the middle
            min_val = min(min(cost[row][prev_col-1], cost[row][prev_col]), cost[row][prev_col+1]);
            if (min_val == cost[row][prev_col-1]) {
                seam[row] = prev_col - 1;
            } else if (min_val == cost[row][prev_col]) {
                seam[row] = prev_col;
            } else {
                seam[row] = prev_col + 1;
            }
        }
    }

    return seam;

}



// REQUIRES: seam is of size image_ height and each element in seam is between
//           [0, image width). image_ is a rectangle of pixels.
// MODIFIES: image_
// EFFECTS: Removes one pixel from each row from the image per the col value
//          found in the seam.
// MP PART: 2
void RemoveVerticalSeam(Image& image_, const std::vector<int>& seam) {

    for (int i = 0; i < image_.Height(); i++) {
        image_.RemovePixel(i, seam[i]);
    }

}