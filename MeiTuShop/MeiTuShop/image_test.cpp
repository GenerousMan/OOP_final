//
// Created by Wen Jiang on 6/19/18.
//
#include "ImageProcess.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>

int main(int argc, char *argv[]) {
    ImageProcessor img = cv::imread("../test_image/lena.bmp");
    auto n_img = img.hue(-50);
    QApplication a(argc, argv);
    QLabel *l = new QLabel();
    l->setPixmap(QPixmap::fromImage(n_img.to_QImage()));
    l->show();
    return a.exec();
}
