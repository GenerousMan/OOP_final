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
#include <QtGui/QImage>
#include <vector>

class ImageProcessor {
public:
    ImageProcessor() = default;

    ImageProcessor(const cv::Mat &img) {
        m_img = img.clone();
    }

    ImageProcessor(QImage const &img, unsigned int format = CV_8UC3);

    ImageProcessor &operator=(QImage const &img);

    ImageProcessor &operator=(const ImageProcessor &img_pro);

    ImageProcessor &operator=(const cv::Mat &img);

    explicit operator QImage() const;

    //For debug convenience
    explicit operator cv::Mat() const;

    //For debug convenience
    void imshow(const std::string &name = "test") const;

    // rotate image
    // @angle: angle to rotate
    // @return an image processor obejct with rotated image.
    ImageProcessor rotation(double angle) const;

    // Crop image
    ImageProcessor crop(cv::Rect rect);

    // TO gray image.
    ImageProcessor gray() const;

    // Change contrast, 1.0 means no change
    ImageProcessor contraast(double alpha) const;

    // Change light, 0 means no change
    ImageProcessor light(double beta) const;

    // Auto histogram equalize
    ImageProcessor histogram_equalize() const;

    // Auto enhance by Laplace operator
    ImageProcessor enhance() const;

    ImageProcessor log_enhance() const;

    ImageProcessor gamma_adjust() const;

    // Detail keep butter to be intensity/3
    // intensity = 10 seems good.
    ImageProcessor buffing(int intensity = 10, int detail_keep = 3) const;

    // Whiten skin, beta is streng of whitening.
    // beta=2 means no change.
    ImageProcessor whitening(double beta = 2) const;

    // Adjust saturate
    // shift is shift value in (-255, 255)
    ImageProcessor saturation(char shift = 20) const;

    //Adjust hue
    // shift is shift value in (-255, 255)
    ImageProcessor hue(char shift = 20) const;

    // Auto white balance
    ImageProcessor white_balance() const;

    // convert to QImage, return a copy;
    QImage to_QImage(QImage::Format format = QImage::Format_RGB888) const;

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

QImage ImageProcessor::to_QImage(QImage::Format format) const {
    cv::Mat temp_img;
    cv::cvtColor(m_img, temp_img, cv::COLOR_BGR2RGB);
    return QImage(temp_img.data, temp_img.cols, temp_img.rows,
                  static_cast<int>(temp_img.step), format).copy();
}

ImageProcessor::operator QImage() const {
    return this->to_QImage();
}

ImageProcessor::operator cv::Mat() const {
    return m_img.clone();
}

ImageProcessor::ImageProcessor(QImage const &img, unsigned int format) {
    auto temp_img = cv::Mat(img.height(), img.width(), format, const_cast<uchar *>(img.bits()),
                            static_cast<size_t>(img.bytesPerLine())).clone();
    cv::cvtColor(temp_img, m_img, CV_RGB2BGR);
}

ImageProcessor &ImageProcessor::operator=(QImage const &img) {
    this->m_img = cv::Mat(img.height(), img.width(), CV_8UC3, const_cast<uchar *>(img.bits()),
                          static_cast<size_t>(img.bytesPerLine())).clone();
    return *this;
}

ImageProcessor &ImageProcessor::operator=(const ImageProcessor &img_pro) {
    this->m_img = img_pro.m_img.clone();
    return *this;
}

ImageProcessor &ImageProcessor::operator=(const cv::Mat &img) {
    m_img = img.clone();
    return *this;
}

ImageProcessor ImageProcessor::gray() const {
    cv::Mat temp_img;
    cv::cvtColor(m_img, temp_img, cv::COLOR_BGR2GRAY);
    cv::Mat final_img;
    cv::cvtColor(temp_img, final_img, cv::COLOR_GRAY2BGR);
    return final_img;
}

ImageProcessor ImageProcessor::contraast(double alpha) const {
    cv::Mat new_img = cv::Mat::zeros(m_img.size(), m_img.type());
    for (int y = 0; y < m_img.rows; y++) {
        for (int x = 0; x < m_img.cols; x++) {
            for (int c = 0; c < 3; c++) {
                new_img.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(
                        alpha * (m_img.at<cv::Vec3b>(y, x)[c]));
            }
        }
    }
    return new_img;
}

ImageProcessor ImageProcessor::light(double beta) const {
    cv::Mat new_img = cv::Mat::zeros(m_img.size(), m_img.type());
    for (int y = 0; y < m_img.rows; y++) {
        for (int x = 0; x < m_img.cols; x++) {
            for (int c = 0; c < 3; c++) {
                new_img.at<cv::Vec3b>(y, x)[c] = cv::saturate_cast<uchar>(
                        (m_img.at<cv::Vec3b>(y, x)[c]) + beta);
            }
        }
    }
    return new_img;
}

ImageProcessor ImageProcessor::histogram_equalize() const {
    auto result = m_img.clone();
    cv::equalizeHist(m_img, result);
    return result;
}

ImageProcessor ImageProcessor::enhance() const {
    cv::Mat enhanced_img;
    cv::Matx33f kernel(0, -1, 0, // Laplace operator
                       0, 5, 0,
                       0, -1, 0);
    filter2D(m_img, enhanced_img, CV_8UC3, kernel);
    return enhanced_img;
}

ImageProcessor ImageProcessor::log_enhance() const {
    cv::Mat log_img(m_img.size(), CV_32FC3);
    for (int i = 0; i < m_img.rows; i++) {
        for (int j = 0; j < m_img.cols; j++) {
            log_img.at<cv::Vec3f>(i, j)[0] = static_cast<float>(log(1 + m_img.at<cv::Vec3b>(i, j)[0]));
            log_img.at<cv::Vec3f>(i, j)[1] = static_cast<float>(log(1 + m_img.at<cv::Vec3b>(i, j)[1]));
            log_img.at<cv::Vec3f>(i, j)[2] = static_cast<float>(log(1 + m_img.at<cv::Vec3b>(i, j)[2]));
        }
    }
    cv::normalize(log_img, log_img, 0, 255, CV_MINMAX);
    cv::convertScaleAbs(log_img, log_img);
    return log_img;
}

ImageProcessor ImageProcessor::gamma_adjust() const {
    cv::Mat gamma_img(m_img.size(), CV_32FC3);
    for (int i = 0; i < m_img.rows; i++) {
        for (int j = 0; j < m_img.cols; j++) {
            gamma_img.at<cv::Vec3f>(i, j)[0] = (m_img.at<cv::Vec3b>(i, j)[0]) * (m_img.at<cv::Vec3b>(i, j)[0]) *
                                               (m_img.at<cv::Vec3b>(i, j)[0]);
            gamma_img.at<cv::Vec3f>(i, j)[1] = (m_img.at<cv::Vec3b>(i, j)[1]) * (m_img.at<cv::Vec3b>(i, j)[1]) *
                                               (m_img.at<cv::Vec3b>(i, j)[1]);
            gamma_img.at<cv::Vec3f>(i, j)[2] = (m_img.at<cv::Vec3b>(i, j)[2]) * (m_img.at<cv::Vec3b>(i, j)[2]) *
                                               (m_img.at<cv::Vec3b>(i, j)[2]);
        }
    }
    cv::normalize(gamma_img, gamma_img, 0, 255, CV_MINMAX);
    cv::convertScaleAbs(gamma_img, gamma_img);
    return gamma_img;
}

ImageProcessor ImageProcessor::buffing(int intensity, int detail_keep) const {
    cv::Mat result;
    int dx = intensity * 5;
    double fc = intensity * 12.5;
    int p = 50;
    cv::Mat temp1, temp2, temp3, temp4;

    cv::bilateralFilter(m_img, temp1, dx, fc, fc);

    temp2 = (temp1 - m_img + 128);

    cv::GaussianBlur(temp2, temp3, cv::Size(2 * detail_keep - 1, 2 * detail_keep - 1), 0, 0);

    temp4 = m_img + 2 * temp3 - 255;

    result = (m_img * (100 - p) + temp4 * p) / 100;
    return result;
}

ImageProcessor ImageProcessor::whitening(double beta) const {
    cv::Mat result;
    cv::Mat result_f;
    cv::Mat temp;
    m_img.convertTo(temp, CV_32FC3);
    temp = temp * (beta - 1) + 1;
    cv::log(temp, result_f);
    result_f = result_f / cv::log(beta);
    cv::normalize(result_f, result_f, 0, 255, CV_MINMAX);
    cv::convertScaleAbs(result_f, result_f);
    result_f.convertTo(result, CV_8UC3);
    return result;
}

ImageProcessor ImageProcessor::white_balance() const {
    cv::Mat result;
    std::vector<cv::Mat> imageRGB;

    cv::split(m_img, imageRGB);

    double R, G, B;
    B = cv::mean(imageRGB[0])[0];
    G = cv::mean(imageRGB[1])[0];
    R = cv::mean(imageRGB[2])[0];

    double KR, KG, KB;
    KB = (R + G + B) / (3 * B);
    KG = (R + G + B) / (3 * G);
    KR = (R + G + B) / (3 * R);

    imageRGB[0] = imageRGB[0] * KB;
    imageRGB[1] = imageRGB[1] * KG;
    imageRGB[2] = imageRGB[2] * KR;

    cv::merge(imageRGB, result);
    return result;
}

ImageProcessor ImageProcessor::saturation(const char shift) const {
    cv::Mat hsv;
    cv::cvtColor(m_img, hsv, CV_BGR2HSV);
    for (int j = 0; j < m_img.rows; j++) {
        for (int i = 0; i < m_img.cols; i++) {
            signed short s = hsv.at<cv::Vec3b>(j, i)[1];
            signed short s_stable = s;
            s_stable += shift;

            if (s_stable < 0)
                s = static_cast<short>(180 + s_stable);
            else if (s_stable > 180)
                s = static_cast<short>(s_stable - 180);
            else
                s = s_stable;
            hsv.at<cv::Vec3b>(j, i)[1] = static_cast<unsigned char>(s);
        }
    }
    cv::Mat result;
    cvtColor(hsv, result, CV_HSV2BGR);
    return result;
}

ImageProcessor ImageProcessor::hue(const char shift) const {
    cv::Mat hsv;
    cv::cvtColor(m_img, hsv, CV_BGR2HSV);
    for (int j = 0; j < m_img.rows; j++) {
        for (int i = 0; i < m_img.cols; i++) {
            signed short h = hsv.at<cv::Vec3b>(j, i)[0];
            signed short h_stable = h;
            h_stable += shift;

            if (h_stable < 0)
                h = static_cast<short>(180 + h_stable);
            else if (h_stable > 180)
                h = static_cast<short>(h_stable - 180);
            else
                h = h_stable;
            hsv.at<cv::Vec3b>(j, i)[0] = static_cast<unsigned char>(h);
        }
    }
    cv::Mat result;
    cvtColor(hsv, result, CV_HSV2BGR);
    return result;
}

#endif //OOP_FINAL_IMAGEPROCESS_H

