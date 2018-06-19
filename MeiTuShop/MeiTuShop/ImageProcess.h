//
// Created by Wen Jiang on 6/19/18.
//

#ifndef OOP_FINAL_IMAGEPROCESS_H
#define OOP_FINAL_IMAGEPROCESS_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include <utility>

class ImageProcessor {
public:

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
    void imshow() const {
        cv::namedWindow("Test");
        cv::imshow("Test", m_img);
        cv::waitKey(0);
        cv::destroyWindow("Test");
    }


    // rotate image
    // @angle: angle to rotate
    // @return an image processor obejct with rotated image.
    ImageProcessor rotation(double angle) const;

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

#endif //OOP_FINAL_IMAGEPROCESS_H
