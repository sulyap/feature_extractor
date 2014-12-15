#ifndef GLCM_FEATURE_EXTRACTOR_H_
#define GLCM_FEATURE_EXTRACTOR_H_

#define ANGLE_90 1
#define ANGLE_45 2
#define ANGLE_180 3
#define ANGLE_135 4

#include <iostream>
#include <vector>
#include <exception>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "feature_extractor.hpp"

using namespace std;
using namespace cv;

class GLCMFeatureExtractor: public FeatureExtractor
{

public:
  int direction;
  Mat glcmVisual;
  Mat glcmNormalized;

  GLCMFeatureExtractor(Mat image, int direction);
  vector<float> getFeatures();

  bool isValidPixel(int r, int c, int max_row, int max_col);
};

#endif
