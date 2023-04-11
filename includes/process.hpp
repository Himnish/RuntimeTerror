#ifndef PROCESS_HPP
#define PROCESS_HPP
#include <fstream>
#include <vector>
#include <string>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/face.hpp>
#include <opencv2/videoio.hpp>

// Code based off of https://docs.opencv.org/3.4/da/d60/tutorial_face_main.html
// Code based off of https://www.pyimagesearch.com/2018/09/24/opencv-face-recognition/


class Process{
    public:

    void FaceDatasetRead(std::vector<cv::Mat>& data, std::vector<int>& desc);
    std::string GetFaceIdentification();
    void FaceRecModelTrainer();
    void FaceAdd();
    void FaceRec(std::vector<cv::Rect> data);

    private:

    std::string str = "";
    
};







#endif
