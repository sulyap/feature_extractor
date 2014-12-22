#ifndef LBP_FEATURE_EXTRACTOR_H_
#define LBP_FEATURE_EXTRACTOR_H_

#include <iostream>
#include <vector>
#include <exception>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "feature_extractor.hpp"
#include "histo_util.hpp"

using namespace std;
using namespace cv;

class LBPFeatureExtractor: public FeatureExtractor
{

public:
  int cell_size;
  int num_bins;
  Mat lbpVisual;
  LBPFeatureExtractor(Mat image, int num_bins, int cell_size);
  vector<float> getFeatures();

  bool isValidPixel(int r, int c, int max_row, int max_col);
};

#endif
