#include "lbp_feature_extractor.hpp"

LBPFeatureExtractor::LBPFeatureExtractor(Mat image, int num_bins, int cell_size): FeatureExtractor(image) {

  this->num_bins = num_bins;
  this->cell_size = cell_size;

  Mat lbpImage;
  image.copyTo(lbpImage);

  int rows = image.rows;
  int cols = image.cols;

  for(int row = 0; row < rows; row++) {
    for(int col = 0; col < cols; col++) {
      int currentValue = (int)image.at<uchar>(row, col);
      int lbpValue = 0;

      int ul = ((row - 1) >= 0 && (col - 1) >= 0) ? (int)image.at<uchar>((row - 1), (col - 1)) : 0;
      if(ul > currentValue)
        lbpValue += pow(2, 7);

      int top = ((row - 1) >= 0 && col >= 0) ? (int)image.at<uchar>((row - 1), col) : 0;
      if(top > currentValue)
        lbpValue += pow(2, 6);

      int ur = ((row - 1) >= 0 && (col + 1) >= 0) ? (int)image.at<uchar>((row - 1), (col + 1)) : 0;
      if(ur > currentValue)
        lbpValue += pow(2, 5);

      int right = (row >= 0 && (col + 1) >= 0) ? (int)image.at<uchar>(row, (col + 1)) : 0;
      if(right > currentValue)
        lbpValue += pow(2, 4);

      int lr = ((row + 1) >= 0 && (col + 1) >= 0) ? (int)image.at<uchar>((row + 1), (col + 1)) : 0;
      if(lr > currentValue)
        lbpValue += pow(2, 3);

      int bottom = ((row + 1) >= 0 && col >= 0) ? (int)image.at<uchar>((row + 1), col) : 0;
      if(bottom > currentValue)
        lbpValue += pow(2, 2);

      int ll = ((row + 1) >= 0 && (col - 1)) >= 0 ? (int)image.at<uchar>((row + 1), (col - 1)) : 0;
      if(ll > currentValue)
        lbpValue += pow(2, 1);

      int left = (row >= 0 && (col - 1) >= 0) ? (int)image.at<uchar>(row, (col - 1)) : 0;
      if(left > currentValue)
        lbpValue += pow(2, 0);

      //printf("Current value: %d LBP Value: %d\n", currentValue, lbpValue);
      lbpImage.at<uchar>(row, col) = lbpValue;
    }
  }

  lbpImage.copyTo(lbpVisual);
}

vector<float> LBPFeatureExtractor::getFeatures() {
  vector<float> features;

  return features;
}
