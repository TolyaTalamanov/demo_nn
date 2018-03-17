#include <iostream>
#include <memory>

#include "detector.h"

using namespace std;

int main (int argc, char** argv) {
	const string model_file = "../models/SSD_300x300/deploy.prototxt";
	const string weight_file = "../models/SSD_300x300/VGG_VOC0712_SSD_300x300_iter_120000.caffemodel";
	const string mean_file = "";
	const string mean_value = "104,117,123";
	const string img_path = argv[1];
	const double conf_treshold = 0.5;

	cv::Mat img = cv::imread(img_path);

	Detector detector(model_file, weight_file, mean_file, mean_value);
	auto detections = detector.Detect(img);
	for (const auto& d : detections) {
		if (d[2] > conf_treshold) {
			cv::Rect bounding_box(static_cast<int>(d[3] * img.cols), static_cast<int>(d[4] * img.rows), 
														static_cast<int>(d[5] * img.cols), static_cast<int>(d[6] * img.rows));
			cv::rectangle(img, bounding_box, cv::Scalar(0, 0, 255));
		}
	}
	cv::imshow("window", img);
	cv::waitKey(0);

	return 0;
}

