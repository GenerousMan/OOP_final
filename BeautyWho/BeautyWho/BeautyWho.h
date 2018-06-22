#pragma once
#ifndef BEAUTYWHO_H
#define BEAUTYWHO_H
#include <QtWidgets/QMainWindow>
#include "ui_BeautyWho.h"
#include "opencv2/opencv.hpp"
using namespace cv;

class BeautyWho : public QMainWindow
{
	Q_OBJECT

public:
	BeautyWho(QWidget *parent = Q_NULLPTR);

private slots:
	void open_pic();

private:
	Ui::BeautyWhoClass *ui;
	QLabel *label;
};

#endif //OOP_FINAL_BEAUTYWHO_H