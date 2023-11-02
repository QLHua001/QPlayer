#pragma once

#include <string>
#include <set>

class QPlayer{

public:
    void playVideo(const std::string& videoPath);
    void playImage(const std::string& imgPath);
    void play(cv::Mat frame);
    void play(const std::vector<std::string>& playlist);

private:
    std::set<std::string> _supportedVideoTypes{".mp4", ".avi"};
    std::set<std::string> _supportedImageTypes{".jpg", ".png"};
};