#ifndef VISUALS_FACEDETECTOR_F
#define VISUALS_FACEDETECTOR_F
#include <opencv4/opencv2/dnn.hpp>
#include <thread>

class CameraControl {
  public:
    CameraControl();
    void CameraStart();
    int EscapeCameraNow();
  private:
    //std::thread threadObj;
};
#endif