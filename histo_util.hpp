#ifndef HISTO_UTIL_H_
#define HISTO_UTIL_H_

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

class HistoUtil
{
public:
  static vector<float> matrixToVector(Mat input);
  static float getMin(vector<float> nums);
  static float getMax(vector<float> nums);
  static vector<float> computeMatrixHistogram(Mat matrix, float min_val, float max_val, int bins);
  static vector<float> computeVectorHistogram(vector<float> values, float min_val, float max_val, int bins);
  static vector<float> normalizeHistogram(vector<float> histogram);
  static float getHistoMean(vector<float> histogram);
  static float getHistoStdDev(vector<float> histogram);
  static float getHistoSkew(vector<float> histogram);
  static float getHistoKurtosis(vector<float> histogram);
  static float getHistoEnergy(vector<float> histogram);
};

#endif
