//
// Created by Wen Jiang on 6/19/18.
//

#ifndef OOP_FINAL_IMAGEPROCESS_H
#define OOP_FINAL_IMAGEPROCESS_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <utility>
#include <string>
#include <exception>

class ImageProcessor {
public:
    ImageProcessor() = default;

    ImageProcessor(const cv::Mat &img) {
        m_img = img.clone();
    }

    ImageProcessor &operator=(const ImageProcessor &img_pro) {
        this->m_img = img_pro.m_img.clone();
        return *this;
    }

    ImageProcessor &operator=(const cv::Mat &img) {
        m_img = img.clone();
        return *this;
    }

    //For debug convenience
    explicit operator cv::Mat() const {
        return m_img.clone();
    }

    //For debug convenience
    void imshow(const std::string &name = "test") const;

    // rotate image
    // @angle: angle to rotate
    // @return an image processor obejct with rotated image.
    ImageProcessor rotation(double angle) const;

    ImageProcessor crop(cv::Rect rect);

    ~ImageProcessor() = default;

private:
    cv::Mat m_img;

};

ImageProcessor ImageProcessor::rotation(double angle) const {
    int width = m_img.cols;
    int height = m_img.rows;

    // Calculate center point
    cv::Point2f center;
    center.x = static_cast<float>(width / 2.0);
    center.y = static_cast<float>(height / 2.0);

    // Get transform matrix
    double scale = 1.0;
    cv::Mat trans_mat = getRotationMatrix2D(center, -angle, scale);

    // Calculate image size
    double angle1 = angle * CV_PI / 180.;
    double a = sin(angle1) * scale;
    double b = cos(angle1) * scale;
    double out_width = height * fabs(a) + width * fabs(b);
    double out_height = width * fabs(a) + height * fabs(b);

    // Rotate with shift.
    trans_mat.at<double>(0, 2) += cvRound((out_width - width) / 2);
    trans_mat.at<double>(1, 2) += cvRound((out_height - height) / 2);

    // Affine transform
    cv::warpAffine(m_img, trans_mat, trans_mat,
                   cv::Size(static_cast<int>(out_width), static_cast<int>(out_height)));

    return trans_mat;
}

void ImageProcessor::imshow(const std::string &name) const {
    cv::namedWindow(name);
    cv::imshow(name, m_img);
    cv::waitKey(0);
    cv::destroyWindow(name);
}

ImageProcessor ImageProcessor::crop(cv::Rect rect) {
    ImageProcessor croped_img;
    // Calculation crop rectangle.
    cv::Rect srcRect(0, 0, m_img.cols, m_img.rows);
    rect = rect & srcRect;
    if (rect.width <= 0 || rect.height <= 0)
        throw std::runtime_error("witdh and height should > 0");

    croped_img.m_img.create(cv::Size(rect.width, rect.height), m_img.type());
    m_img(rect).copyTo(croped_img.m_img);
    return croped_img;
}

#endif //OOP_FINAL_IMAGEPROCESS_H
