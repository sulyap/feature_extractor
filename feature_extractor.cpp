#include "feature_extractor.hpp"

FeatureExtractor::FeatureExtractor(Mat image)
{
  image.copyTo(this->image);
  cvtColor(this->image, grayscaleImage, CV_BGR2GRAY);
  this->width = image.cols;
  this->height = image.rows;
}
