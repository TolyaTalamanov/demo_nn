#ifndef DETECTOR_DETECTOR_HPP_
#define DETECTOR_DETECTOR_HPP_

#include <vector>
#include <string>
#include <memory>
#include <caffe/caffe.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using std::string;
using std::vector;

class Detector {
 public:
  Detector(const string& model_file,
           const string& weights_file,
           const string& mean_file,
           const string& mean_value);

	vector<vector<float> > Detect(int img_h, int img_w,
			                          unsigned char* data,
																size_t step);

 private:
  void SetMean(const string& mean_file, const string& mean_value);

  void WrapInputLayer(vector<cv::Mat>* input_channels);

  void Preprocess(const cv::Mat& img, vector<cv::Mat>* input_channels);

 private:
  std::shared_ptr<caffe::Net<float> > net_;
  cv::Size input_geometry_;
  int num_channels_;
  cv::Mat mean_;
};

#endif  // DETECTOR_DETECTOR_HPP_
