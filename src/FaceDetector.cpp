#include "FaceDetector.h"
#include <opencv4/opencv2/opencv.hpp>
#include <sstream>
#include <string>
#include <vector>

//code based off of https://docs.opencv.org/4.x/dc/d3a/classcv_1_1viz_1_1Camera.html
//and https://github.com/GeorgeSeif/Face-Recognition/blob/master/VideoFaceDetector.cpp

FaceDetector::FaceDetector():
    confidence_(0.5),
    inp_width(300),
    inp_height(300),
    scale_factor_(1.0),
    mean_values_({104.0, 177.0, 123.0}) {
  faces_ = cv::dnn::readNetFromCaffe(FACE_DETECTION_CONFIGURATION,
                                     FACE_DETECTION_WEIGHTS);

  if (faces_.empty()) {
    std::ostringstream ss;
    ss << "Failed to load network";
    throw std::invalid_argument(ss.str());
  }
}

std::vector<cv::Rect> FaceDetector::rect_faces_detected(
    const cv::Mat& chosen_frame_) {
  cv::Mat input_ = cv::dnn::blobFromImage(chosen_frame_,
                                          scale_factor_,
                                          cv::Size(inp_width, inp_height),
                                          mean_values_,
                                          false,
                                          false);
  faces_.setInput(input_, "data");
  cv::Mat detect_ = faces_.forward("detection_out");
  cv::Mat detect_mat_(
      detect_.size[2], detect_.size[3], CV_32F, detect_.ptr<float>());

  std::vector<cv::Rect> faces;

  for (int i = 0; i < detect_mat_.rows; i++) {
    float confidence = detect_mat_.at<float>(i, 2);

    if (confidence < confidence_) {
      continue;
    }
    int x_top_right =
        static_cast<int>(detect_mat_.at<float>(i, 5) * chosen_frame_.cols);
    int x_bot_left =
        static_cast<int>(detect_mat_.at<float>(i, 3) * chosen_frame_.cols);
    int y_top_right =
        static_cast<int>(detect_mat_.at<float>(i, 6) * chosen_frame_.rows);
    int y_bot_left =
        static_cast<int>(detect_mat_.at<float>(i, 4) * chosen_frame_.rows);

    faces.emplace_back(x_bot_left,
                       y_bot_left,
                       (x_top_right - x_bot_left),
                       (y_top_right - y_bot_left));
  }
  //Process::FaceRec(faces);
  return faces;
}