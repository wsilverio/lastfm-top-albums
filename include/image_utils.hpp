#pragma once

#include <opencv2/opencv.hpp>
#include <string>
#include <vector>

class ImageUtils
{
   public:
    static cv::Mat makeGrid(const std::vector<cv::Mat> &images);
    static void saveFile(const cv::Mat &image, const std::string &path);
};
