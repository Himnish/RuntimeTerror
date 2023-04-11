#ifndef VISUALS_FACEDETECTOR_H
#define VISUALS_FACEDETECTOR_H
#include <opencv4/opencv2/dnn.hpp>
#include <thread>

class FaceDetector {
public:
  FaceDetector();
  std::vector<cv::Rect> rect_faces_detected(const cv::Mat& chosen_frame_);

private:
  const float confidence_;
  cv::dnn::Net faces_;
  const int inp_height;
  const int inp_width;
  const double scale_factor_;
  const cv::Scalar mean_values_;
};
#endif
