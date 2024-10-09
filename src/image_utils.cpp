#include "image_utils.hpp"

#include <cmath>
#include <stdexcept>

static bool hasSquareRoot(unsigned n);

cv::Mat ImageUtils::makeGrid(const std::vector<cv::Mat> &images)
{
    if (!hasSquareRoot(images.size()))
        throw std::invalid_argument("Invalid grid size.");

    const auto size = static_cast<unsigned>(std::sqrt(images.size()));
    const auto rows = images.at(0).rows;
    const auto cols = images.at(0).cols;

    cv::Mat grid(rows * size, cols * size, images.at(0).type());

    for (unsigned i = 0; i < size; ++i)
    {
        for (unsigned j = 0; j < size; ++j)
        {
            unsigned index = i * size + j;
            cv::Mat roi = grid(cv::Rect(j * cols, i * rows, cols, rows));
            images.at(index).copyTo(roi);
        }
    }

    return grid;
}

void ImageUtils::saveFile(const cv::Mat &image, const std::string &path)
{
    cv::imwrite(path, image);
}

static bool hasSquareRoot(unsigned n)
{
    unsigned root = static_cast<unsigned>(std::sqrt(n));
    return (root * root) == n;
}
