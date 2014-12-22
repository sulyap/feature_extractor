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

  image_width = main_image.rows;
  image_height = main_image.cols;

  cout << "GLCM Features:" << endl;
  GLCMFeatureExtractor *fe1 = new GLCMFeatureExtractor(main_image, 1);
  cout << "fe1 Features:" << endl;
  vector<float> features1 = fe1->getFeatures();
  for(int i = 0; i < features1.size(); i++) {
    cout << features1.at(i) << " ";
  }
  cout << endl;

  GLCMFeatureExtractor *fe2 = new GLCMFeatureExtractor(main_image, 2);
  cout << "fe2 Features:" << endl;
  vector<float> features2 = fe2->getFeatures();
  for(int i = 0; i < features2.size(); i++) {
    cout << features2.at(i) << " ";
  }
  cout << endl;

  GLCMFeatureExtractor *fe3 = new GLCMFeatureExtractor(main_image, 3);
  cout << "fe3 Features:" << endl;
  vector<float> features3 = fe3->getFeatures();
  for(int i = 0; i < features3.size(); i++) {
    cout << features3.at(i) << " ";
  }
  cout << endl;

  GLCMFeatureExtractor *fe4 = new GLCMFeatureExtractor(main_image, 4);
  cout << "fe4 Features:" << endl;
  vector<float> features4 = fe4-> getFeatures();
  for(int i = 0; i < features4.size(); i++) {
    cout << features4.at(i) << " ";
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

