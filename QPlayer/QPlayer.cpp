#include <unistd.h>
#include <opencv2/opencv.hpp>
#include "QPlayer.h"

void QPlayer::playVideo(const std::string& videoPath){

    if(videoPath.empty()){
        printf("videoPath is empty!\n");
        return;
    }

    cv::VideoCapture videoCap(videoPath);
    if(!videoCap.isOpened()){
        printf("cv::VideoCapture open fail!(%s)\n", videoPath.c_str());
        return;
    }

    cv::Mat frame;
    while(true){
        videoCap >> frame;
        if(frame.empty()) break;

        this->play(frame);
    }

    videoCap.release();

}

void QPlayer::playImage(const std::string& imgPath){

    if(imgPath.empty()){
        printf("imgPath is empty!\n");
        return;
    }

    cv::Mat frame = cv::imread(imgPath);
    if(frame.empty()){
        printf("cv::imread fail!(%s)\n", imgPath.c_str());
        return;
    }

    this->play(frame);

}

void QPlayer::play(cv::Mat frame){

    cv::imwrite("./temp/frame.jpg", frame);
    usleep(500*1000);

}

void QPlayer::play(const std::vector<std::string>& playlist){

    for(const auto& item : playlist){
        const char* selfExtension = strrchr(item.c_str(), '.');
        if(this->_supportedVideoTypes.count(selfExtension)){
            this->playVideo(item);
        }else if(this->_supportedImageTypes.count(selfExtension)){
            this->playImage(item);
        }
    }

}