#include "glcm_feature_extractor.hpp"

GLCMFeatureExtractor::GLCMFeatureExtractor(Mat image, int direction): FeatureExtractor(image) {
  this->direction = direction;

  // Create an empty 256x256 matrix
  Mat glcmMatrix = Mat::zeros(256, 256, CV_32F);

  for(int r = 0; r < image.rows; r++) {
    for(int c = 0; c < image.cols; c++) {
      // Set the examined pixel depending on angle direction
      int rowNext = r;
      int colNext = c;

      if(direction == ANGLE_90) {
        rowNext = r - 1;
        colNext - c;
      } else if(direction == ANGLE_45) {
        rowNext = r - 1;
        colNext = c + 1;
      } else if(direction == ANGLE_180) {
        rowNext = r;
        colNext = c + 1;
      }
      else if(direction == ANGLE_135) {
        rowNext = r + 1;
        colNext = c + 1;
      }

      if(isValidPixel(r, c, (height - 1), (width - 1)) &&
          isValidPixel(rowNext, colNext, (height - 1), (width - 1))) {
        float valCurrent = grayscaleImage.at<uchar>(r, c);
        float valNext = grayscaleImage.at<uchar>(rowNext, colNext);

        // Symmetrical GLCM occurence count
        glcmMatrix.at<float>(valCurrent, valNext) = glcmMatrix.at<float>(valCurrent, valNext) + 1;
        glcmMatrix.at<float>(valNext, valCurrent) = glcmMatrix.at<float>(valNext, valCurrent) + 1;
      }
    }
  }

  // Get sum for normalization
  float n = 0;
  float min = 0;
  float max = 0;
  for(int r = 0; r < glcmMatrix.rows; r++) {
    for(int c = 0; c < glcmMatrix.cols; c++) {
      n = n + (float)glcmMatrix.at<float>(r, c); 

      if(glcmMatrix.at<float>(r, c) > max)
        max = glcmMatrix.at<float>(r, c);
    }
  }

  Mat visualMatrix = Mat::zeros(256, 256, CV_8UC3);
  glcmVisual = Mat::zeros(256, 256, CV_8UC3);
  glcmNormalized = Mat::zeros(256, 256, DataType<float>::type);
  for(int r = 0; r < 256; r++) {
    for(int c = 0; c < 256; c++) {
      float normalized = (glcmMatrix.at<float>(r, c) / n);
      glcmNormalized.at<float>(r, c) = normalized;

      float normalizedVisualValue = (glcmMatrix.at<float>(r, c) - min) / (max - min) * 255;
      int newVisualValue = roundf(normalizedVisualValue);
      glcmVisual.at<Vec3b>(r, c)[0] = newVisualValue;
      glcmVisual.at<Vec3b>(r, c)[1] = newVisualValue;
      glcmVisual.at<Vec3b>(r, c)[2] = newVisualValue;
    }
  }

  cvtColor(glcmVisual, glcmVisual, CV_BGR2GRAY);

  // Setup mean, variance and p
  this->p = getP();
  this->mean = getMean();
  this->variance = getVariance();

  this->correlation = 0;
  this->energy = 0;
  this->contrast = 0;
  this->dissimilarity = 0;
  this->homogenity = 0;

  for(int r = 0; r < glcmNormalized.rows; r++) {
    for(int c = 0; c < glcmNormalized.cols; c++) {
      this->correlation += ((glcmNormalized.at<float>(r, c) * (r * c)) - (this->mean * this->mean)) / (this->variance * this->variance);
      this->contrast += pow((r - c), 2) * glcmNormalized.at<float>(r, c);
      if(this->contrast != this->contrast) {
        cout << "ERROR. NAN DETECTED FOR CONTRAST" << endl;
      }

      if(glcmNormalized.at<float>(r, c) > 0) {
        this->energy += pow(glcmNormalized.at<float>(r, c), 2);
        this->entropy += glcmNormalized.at<float>(r, c) * log(glcmNormalized.at<float>(r, c));
        this->dissimilarity += glcmNormalized.at<float>(r, c) * abs(r - c);
        this->homogenity += glcmNormalized.at<float>(r, c) / (1 + pow((r - c), 2));
      }
    }
  }

  this->entropy = -this->entropy;
}

vector<float> GLCMFeatureExtractor::getFeatures() {
  vector<float> features;

  features.push_back(this->energy);
  features.push_back(this->contrast);
  features.push_back(this->entropy);
  features.push_back(this->dissimilarity);
  features.push_back(this->homogenity);
  features.push_back(this->correlation);

  return features;
}


float GLCMFeatureExtractor::getVariance() {
  float result = 0;

  for(int r = 0; r < glcmNormalized.rows; r++) {
    result += pow((this->p - this->mean), 2);
  }

  return result;
}

float GLCMFeatureExtractor::getP() {
  float result = 0;

  for(int r = 0; r < glcmNormalized.rows; r++) {
    result += glcmNormalized.at<float>(r, r);
  }

  return result;
}

float GLCMFeatureExtractor::getMean() {
  float result = 0;

  for(int r = 0; r < glcmNormalized.rows; r++) {
    result += glcmNormalized.at<float>(r, r) * r;
  }

  return result;
}

bool GLCMFeatureExtractor::isValidPixel(int r, int c, int max_row, int max_col) {
  if(r < 0 || r > max_row || c < 0 || c > max_col) {
    return false;
  } else {
    return true;
  }
}
