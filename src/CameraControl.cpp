#include "CameraControl.hpp"

#include <opencv4/opencv2/opencv.hpp>
#include <thread>

#include "FaceDetector.hpp"

CameraControl::CameraControl() {
  CamerStart();
}

//code based off of https://docs.opencv.org/4.x/dc/d3a/classcv_1_1viz_1_1Camera.html
//and https://github.com/GeorgeSeif/Face-Recognition/blob/master/VideoFaceDetector.cpp
//and https://towardsdatascience.com/face-detection-models-which-to-use-and-why-d263e82c302c

void CameraControl::CameraStart() {
  cv::VideoCapture cap;
  if (!cap.open(0)) {
    return;
  }
  cv::Mat chosen_frame_;
  FaceDetector detect;
  while (true) {
    cap >> chosen_frame_;
    cv::Scalar color(0, 100, 205);
    auto rectangles = detect.rect_faces_detected(chosen_frame_);
    for (const auto& r : rectangles) {
      cv::rectangle(chosen_frame_, r, color, 4);
    }
    imshow("Image", chosen_frame_);

    if (cv::waitKey(10) == EscapeCameraNow()) {
      break;
    }
  }
  cv::destroyAllWindows();
  cap.release();
  return;
}

int CameraControl::EscapeCameraNow() {
  return 27;
}
