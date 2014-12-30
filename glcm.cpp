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

void syntax() {
  printf("feature_selector [image]\n");
}

bool dirExists(const char *dir_path)  {
  struct stat info;

  if(stat(dir_path, &info) != 0) {
    printf("Cannot access %s\n", dir_path);
    return false;
  } else if(info.st_mode & S_IFDIR) {
    printf("%s is a directory\n", dir_path); 
    return true;
  } else {
    printf("%s is not a directory\n", dir_path); 
    return false;
  }
}

int main(int argc, char **argv) { 
  if(argc != 2) {
    syntax();
    exit(-1);
  }

  main_image = imread(argv[1]);

  vector<float> features;

  GLCMFeatureExtractor *fe1 = new GLCMFeatureExtractor(main_image, 1);
  for(int i = 0; i < fe1->getFeatures().size(); i++) {
    features.push_back(fe1->getFeatures().at(i));
  }

  GLCMFeatureExtractor *fe2 = new GLCMFeatureExtractor(main_image, 2);
  for(int i = 0; i < fe2->getFeatures().size(); i++) {
    features.push_back(fe2->getFeatures().at(i));
  }

  GLCMFeatureExtractor *fe3 = new GLCMFeatureExtractor(main_image, 3);
  for(int i = 0; i < fe3->getFeatures().size(); i++) {
    features.push_back(fe3->getFeatures().at(i));
  }

  GLCMFeatureExtractor *fe4 = new GLCMFeatureExtractor(main_image, 4);
  for(int i = 0; i < fe4->getFeatures().size(); i++) {
    features.push_back(fe4->getFeatures().at(i));
  }

  // Output features
  for(int i = 0; i < features.size(); i++) {
    cout << features.at(i);
    if(i != features.size() - 1)
      cout << ",";
  }
  cout << endl;

  /*
  imshow("1", fe1->glcmVisual);
  imshow("2", fe2->glcmVisual);
  imshow("3", fe3->glcmVisual);
  imshow("4", fe4->glcmVisual);
  waitKey(0);
  */

  return 0;
}


