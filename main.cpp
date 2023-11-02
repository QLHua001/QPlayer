#include <unistd.h>
#include <dirent.h>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

#include "QPlayer/QPlayer.h"

static bool searchSpecifiedFiles(std::string folder, std::string extension, std::vector<std::string>& filePaths){

    if(folder.empty() || extension.empty()) return false; 

    if(folder.back() != '/'){
        folder += "/";
    }

    DIR* pDir;
    dirent* pCur;

    if((pDir = opendir(folder.c_str())) == NULL){
        printf("opendir %s fail!\n", folder.c_str());
        return false;
    }

    while((pCur = readdir(pDir)) != NULL){
        if(DT_REG == pCur->d_type){
            const char* selfExtension = strrchr(pCur->d_name, '.');
            if(selfExtension != NULL && strcmp(selfExtension, extension.c_str()) == 0){
                std::string filePath = folder + pCur->d_name;
                filePaths.push_back(filePath);
            }
        }
    }

    return true;
}

void test(){

    std::string videoPath{"./example/test.mp4"};

    cv::VideoCapture videoCap(videoPath);
    if(!videoCap.isOpened()){
        printf("cv::VideoCapture open fail!(%s)\n", videoPath.c_str());
        return;
    }

    cv::Mat frame;
    while(true){
        videoCap >> frame;
        if(frame.empty()) break;

        cv::imwrite("./temp/frame.jpg", frame);
        usleep(2*1000*1000);
    }

    videoCap.release();

}

void test_QPlayer(){

    std::string root{"/QMy-File2/QDatasets2/BSJ_DMS_MTN_TEST/CloseEye/videos/CloseEye.v.2023.09.15/pos/normal/"};
    
    std::vector<std::string> filePaths;
    searchSpecifiedFiles(root, ".mp4", filePaths);
    printf("Found %ld files.\n", filePaths.size());

    QPlayer player;
    player.play(filePaths);

}

int main(int, char**){
    std::cout << "Hello, from QPlayer!\n";

    // test();

    test_QPlayer();

    return 0;
}
