#include <iostream>
#include <sstream>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <opencv2/opencv.hpp>

#include "feature_extractor.hpp"
#include "glcm_feature_extractor.hpp"
#include "lbp_feature_extractor.hpp"

using namespace std;
using namespace cv;

Mat main_image;
const char *windowName = "MAIN WINDOW";
int image_width;
int image_height;
const char *directory;

// TODO: Put this in config file
int num_bins = 7;
int cell_size = 16;

void syntax() {
  printf("lbp [image]\n");
}

int main(int argc, char **argv) { 
  if(argc != 2) {
    syntax();
    exit(-1);
  }

  main_image = imread(argv[1]);

  vector<float> features;

  LBPFeatureExtractor *fe = new LBPFeatureExtractor(main_image, num_bins, cell_size);
  features = fe->getFeatures();

  // Output features
  for(int i = 0; i < features.size(); i++) {
    cout << features.at(i);
    if(i != features.size() - 1)
      cout << ",";
  }
  cout << endl;

  return 0;
}



