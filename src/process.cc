
#include <fstream>
#include <vector>
#include <chrono>



#include "process.hpp"

// Code based off of https://docs.opencv.org/3.4/da/d60/tutorial_face_main.html and https://github.com/gursewaks056/FaceDetectionUsingCPP/blob/master/FD.cpp
// Code based off of https://www.pyimagesearch.com/2018/09/24/opencv-face-recognition/

void Process::FaceDatasetRead(std::vector<cv::Mat>& data, std::vector<int>& desc){
    std::vector<std::string> names;
    cv::glob("/Users/sahiththummalapally/Desktop/Dataset", names, false);

    for(size_t i=0; i< names.size(); i++){
        size_t lastOcc = names.at(i).rfind('\\', names.at(i).size());
        str = (names.at(i).substr(lastOcc+1, names.size()));
        
        data.push_back(cv::imread(names.at(i), 0));
        desc.push_back(std::stoi(str.c_str()));
    }
}

std::string Process::GetFaceIdentification(){
    return str;
}

void Process::FaceRecModelTrainer(){
    std::vector<cv::Mat> data;
    std::vector<int> desc;
    FaceDatasetRead(data, desc);
    cv::Ptr<cv::face::EigenFaceRecognizer> rec = cv::face::EigenFaceRecognizer::create();
    rec->train(data, desc);

}

void Process::FaceAdd(){
    cv::VideoCapture vc(0);
    if(vc.isOpened() == false){
        return;
    }
    cv::Mat border;
    while(true){
        vc >> border;
        FaceBoxDetection(border);
        break;
    }
    return;
}

void Process::FaceRec(std::vector<cv::Rect> data){

    // Takes Himnish's FaceDetection vector and pass it through this function
    std::string time;
    std::time_t time2;
    std::string completedTime;
    int label;
    double confidence;
    
     cv::CascadeClassifier cc;
    
     cv::Ptr<cv::face::FaceRecognizer> rec = cv::face::FisherFaceRecognizer::create();
     cv::VideoCapture vc(0);
    if(vc.isOpened() == false){
        return;
    }
     
    while(true){
      cv::Mat start;
      cv::Mat border;
      cv::Mat grayBorder;

      vc >> border;

      if(border.empty() == false){
        start = border.clone();
        cvtColor(start, grayBorder, cv::COLOR_BGR2GRAY);
        cc.detectMultiScale(grayBorder, data, 1.1, 3, 0, cv::Size(100, 100));

        for(size_t i=0; i<data.size(); i++){
            cv::Rect part = data.at(i);
            cv::Mat modif = grayBorder(part);

            cv::Mat image;
            cv::resize(modif, image, cv::Size(300, 300), 1.0, 1.0, cv::INTER_CUBIC);

            label = -1; 
            confidence = 0;
	        rec->predict(image, label, confidence);

            cv::putText(start, "-1", cv::Point(std::max(part.tl().x, 0), std::max(part.tl().y, 0)), cv::FONT_ITALIC, 1.0, CV_RGB(255, 0,0), 1.0);
        }

        time = zoned_time(current_zone(), system_clock::now()));
        time2 =  std::chrono::system_clock::to_time_t(time);
        completedTime = std::ctime(&time2); 

        sqlCode::insertName(str, imshow); 
        cv::imshow(str, start);
        
      }
    }
   
}
