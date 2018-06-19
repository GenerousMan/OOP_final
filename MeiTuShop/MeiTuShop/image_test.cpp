//
// Created by Wen Jiang on 6/19/18.
//
#include "ImageProcess.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>

int main(int argc, char *argv[]) {
    ImageProcessor img = cv::imread("../test_image/lena.bmp");
    auto r_img = img.crop(cv::Rect(0, 0, 256, 256));
    QApplication a(argc, argv);
    QLabel *l = new QLabel();
    l->setPixmap(QPixmap::fromImage(img.to_QImage()));
    l->show();
    return a.exec();
}
