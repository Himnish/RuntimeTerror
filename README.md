# Home Security - RuntimeTerror
Himnish Jain, Om Chhabra, Sahith Thummalapally, Yujie Miao

## Overview
What this system does is turn any old devices into a home security system. What it does is that, if the user approves, it will continually record and analyze the video feed from either the camera’s laptop or any inserted webcam. Whenever an alert is detected, it will ring an alarm and message the owner who gets a photo/video and details of the recorded event. Additionally, the user will be able to remotely control the system, change modes, and see recent alerts. The user can also control this using Alexa. 

### Monitor
If anyone unknown comes into the frame, it will be sent as a message to whoever set up the system.

## Libraries:

- OpenCV
- SQL
- Httpslib

# Sources
code based off of https://docs.opencv.org/4.x/dc/d3a/classcv_1_1viz_1_1Camera.html
and https://github.com/GeorgeSeif/Face-Recognition/blob/master/VideoFaceDetector.cpp
and https://towardsdatascience.com/face-detection-models-which-to-use-and-why-d263e82c302c
and https://docs.opencv.org/3.4/da/d60/tutorial_face_main.html and https://github.com/gursewaks056/FaceDetectionUsingCPP/blob/master/FD.cpp
and https://www.pyimagesearch.com/2018/09/24/opencv-face-recognition/
# Commands to execute:
mkdir build
cd build
cmake ..
cmake --build .
make
./OpenCVFaceDetectorCPP
