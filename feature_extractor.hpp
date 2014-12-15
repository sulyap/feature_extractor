#ifndef FEATURE_EXTRACTOR_H_
#define FEATURE_EXTRACTOR_H_

#include <iostream>
#include <vector>
#include <exception>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class FeatureExtractor
{
public:
  Mat image;
  Mat grayscaleImage;
  int width;
  int height;
  FeatureExtractor(Mat image);
  virtual vector<float> getFeatures() = 0;
};

#endif
