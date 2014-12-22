#include "histo_util.hpp"

vector<float> HistoUtil::matrixToVector(Mat input)
{
  vector<float> data;       
  for(int row = 0; row < input.rows; row++)
  {
    for(int col = 0; col < input.cols; col++)
    {
      float d = (float)input.at<uchar>(row, col);
      data.push_back(d);   
    }
  }

  return data;
}

float HistoUtil::getMin(vector<float> nums)
{
  float min = 0;
  for(int i = 0; i < nums.size(); i++)
  {
    if(min > nums.at(i))
      min = nums.at(i);
  }

  return min;
}

float HistoUtil::getMax(vector<float> nums)
{
  float max = 0;
  for(int i = 0; i < nums.size(); i++)
  {
    if(max < nums.at(i))
      max = nums.at(i);
  }

  return max;
}



// TODO: Assert max_val > min_val
vector<float> HistoUtil::computeMatrixHistogram(Mat matrix, float min_val, float max_val, int bins)
{
  float interval = (max_val - min_val) / bins;
  float counter_low = min_val;
  float counter_high = min_val + interval;

  vector<float> hist;
  for(int i = 0; i < bins; i++)
  {
    hist.push_back(0);
  }

  for(int i = 0; i < bins; i++)
  {
    for(int y = 0; y < matrix.rows; y++)
    {
      for(int x = 0; x < matrix.cols; x++)
      {
        float val;
        if(y > matrix.rows - 1 || y < 0 || x > matrix.cols - 1 || x < 0)
          val = 0;
        else
          val = (float)matrix.at<uchar>(y, x);

        if(counter_low <= val && val <= counter_high)
        {
          hist.at(i) += 1;
        }

      }
    }

    counter_low = counter_low + interval;
    counter_high = counter_low + interval;
  }

  return hist;
}

vector<float> HistoUtil::computeVectorHistogram(vector<float> values, float min_val, float max_val, int bins)
{
  float interval = (max_val - min_val) / bins;
  float counter_low = min_val;
  float counter_high = min_val + interval;

  vector<float> hist;
  for(int i = 0; i < bins; i++)
  {
    hist.push_back(0);
  }

  for(int i = 0; i < bins; i++)
  {
    for(int c = 0; c < values.size(); c++)
    {
      float val = values.at(c);
      if(counter_low <= val && val <= counter_high)
      {
        hist.at(i) += 1;
      }
    }

    counter_low = counter_low + interval;
    counter_high = counter_low + interval;
  }

  return hist;
}

vector<float> HistoUtil::normalizeHistogram(vector<float> histogram)
{
  float total = 0;
  vector<float> hist;
  for(int i = 0; i < histogram.size(); i++)
  {
    total += histogram.at(i);
    hist.push_back(0);
  }

  for(int i = 0; i < histogram.size(); i++)
  {
    hist.at(i) = (histogram.at(i) / total) * 100;
  }

  return hist;
}
