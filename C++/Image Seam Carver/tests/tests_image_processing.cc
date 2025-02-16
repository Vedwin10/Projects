/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>

#include "image.hpp"
#include "image_processing.hpp"
#include "tests_helpers.hpp"

using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////
// Test Cases //
///////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("ImageProcessing Flip Left", "[ImageProcessing-FlipLeft]") {
  Image img_proc1("tests/test_images/test4x3.ppm");
  RotateLeft(img_proc1);

  Image img1_rotate_left("tests/test_images/test4x3_left.ppm");
  REQUIRE(CompareImages(img1_rotate_left, img_proc1));
}

TEST_CASE("Calculate Energy 1", "[Calculate-Energy-1]") {
  Image img1("tests/test_images/test2x2_1.ppm");
  vector<vector<int>> ground_truth_energy = CalculateEnergy(img1);

  vector<vector<int>> actual_energy = {{9999, 9999},{9999, 9999}};

  REQUIRE(CompareIntVectors(ground_truth_energy, actual_energy));
}

TEST_CASE("Calculate Energy 2", "[Calculate-Energy-2]") {
  Image img1("tests/test_images/test3x3_1.ppm");
  vector<vector<int>> ground_truth_energy = CalculateEnergy(img1);

  vector<vector<int>> actual_energy = {{9999, 9999, 9999}, {9999, 313, 9999}, {9999, 9999, 9999}};

  REQUIRE(CompareIntVectors(ground_truth_energy, actual_energy));
}

TEST_CASE("Calculate Cost Vertical 1", "[Calculate-Cost-Vertical-1]") {
  vector<vector<int>> energy = {{9999, 9999},{9999, 9999}};

  vector<vector<int>> ground_truth_cost = CalculateCostVertical(energy);

  vector<vector<int>> actual_cost = {{9999, 9999}, {19998, 19998}};

  REQUIRE(CompareIntVectors(ground_truth_cost, actual_cost));
}

TEST_CASE("Calculate Cost Vertical 2", "[Calculate-Cost-Vertical-2]") {
  vector<vector<int>> energy = {{9999, 9999, 9999}, {9999, 313, 9999}, {9999, 9999, 9999}};

  vector<vector<int>> ground_truth_cost = CalculateCostVertical(energy);

  vector<vector<int>> actual_cost = {{9999, 9999, 9999}, {19998, 10312, 19998}, {20311, 20311, 20311}};

  REQUIRE(CompareIntVectors(ground_truth_cost, actual_cost));
}

TEST_CASE("Calculate Cost Vertical 3", "[Calculate-Cost-Vertical-3]") {
  vector<vector<int>> energy = {{5, 1, 8, 6, 3}, {4, 2, 5, 1, 6}, {5, 8, 1, 10, 2}, {3, 3, 3, 3, 3}, {1, 2, 3, 4, 5}};

  vector<vector<int>> ground_truth_cost = CalculateCostVertical(energy);

  vector<vector<int>> actual_cost = {{5, 1, 8, 6, 3}, {5, 3, 6, 4, 9}, {8, 11, 4, 14, 6}, {11, 7, 7, 7, 9}, {8, 9, 10, 11, 12}};

  REQUIRE(CompareIntVectors(ground_truth_cost, actual_cost));
}

TEST_CASE("Find Vertical Seam 1", "[Find-Vertical-Seam-1]") {
  Image img1("tests/test_images/test2x2_1.ppm");
  vector<int> ground_truth_seam_vec = FindVerticalSeam(img1);
  vector<vector<int>> ground_truth_seam = {ground_truth_seam_vec};

  vector<vector<int>> actual_seam = {{0, 0}};

  REQUIRE(CompareIntVectors(ground_truth_seam, actual_seam));
}

TEST_CASE("Find Vertical Seam 2", "[Find-Vertical-Seam-2]") {
  Image img1("tests/test_images/test3x3_1.ppm");
  vector<int> ground_truth_seam_vec = FindVerticalSeam(img1);
  vector<vector<int>> ground_truth_seam = {ground_truth_seam_vec};

  vector<vector<int>> actual_seam = {{0, 1, 0}};

  REQUIRE(CompareIntVectors(ground_truth_seam, actual_seam));
}

// Add more tests below!
// Look inside the tests/test_images folder for sample small images.
// Feel free to also make your own!
// Use the helper functions in tests_helpers.hpp and tests_helpers.cc to compare images.