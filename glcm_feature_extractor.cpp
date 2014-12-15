#include "glcm_feature_extractor.hpp"

GLCMFeatureExtractor::GLCMFeatureExtractor(Mat image, int direction): FeatureExtractor(image)
{
  this->direction = direction;

  // Create an empty 256x256 matrix
  Mat glcmMatrix = Mat::zeros(256, 256, CV_32F);

  for(int r = 0; r < image.rows; r++)
  {
    for(int c = 0; c < image.cols; c++)
    {
      // Set the examined pixel depending on angle direction
      int rowNext = r;
      int colNext = c;

      if(direction == ANGLE_90)
      {
        rowNext = r - 1;
        colNext - c;
      }
      else if(direction == ANGLE_45)
      {
        rowNext = r - 1;
        colNext = c + 1;
      }
      else if(direction == ANGLE_180)
      {
        rowNext = r;
        colNext = c + 1;
      }
      else if(direction == ANGLE_135)
      {
        rowNext = r + 1;
        colNext = c + 1;
      }

      if(isValidPixel(r, c, (height - 1), (width - 1)) &&
          isValidPixel(rowNext, colNext, (height - 1), (width - 1)))
      {
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
  for(int r = 0; r < glcmMatrix.rows; r++)
  {
    for(int c = 0; c < glcmMatrix.cols; c++)
    {
      n = n + (float)glcmMatrix.at<float>(r, c); 

      if(glcmMatrix.at<float>(r, c) > max)
        max = glcmMatrix.at<float>(r, c);
    }
  }

  Mat visualMatrix = Mat::zeros(256, 256, CV_8UC3);
  glcmVisual = Mat::zeros(256, 256, CV_8UC3);
  glcmNormalized = Mat::zeros(256, 256, DataType<float>::type);
  for(int r = 0; r < 256; r++)
  {
    for(int c = 0; c < 256; c++)
    {
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
}

vector<float> GLCMFeatureExtractor::getFeatures()
{
  vector<float> features;

  return features;
}

bool GLCMFeatureExtractor::isValidPixel(int r, int c, int max_row, int max_col)
{
  if(r < 0 || r > max_row || c < 0 || c > max_col)
  {
    return false;
  }
  else
  {
    return true;
  }
}
