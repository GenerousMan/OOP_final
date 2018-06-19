//
// Created by Wen Jiang on 6/19/18.
//
#include "ImageProcess.h"

int main() {
    ImageProcessor img = cv::imread("../test_image/lena.bmp");
    img.imshow();
    auto r_img = img.crop(cv::Rect(0, 0, 256, 256));
    r_img.imshow();
    return 0;
}
