#pragma once

#ifndef BEAUTYWHO_H
#define BEAUTYWHO_H

#include <QtWidgets/QMainWindow>
#include "ui_BeautyWho.h"

class BeautyWho : public QMainWindow
{
	Q_OBJECT

public:
	BeautyWho(QWidget *parent = Q_NULLPTR);

private slots:
	void open_pic();
	void gray_pic();
	void white_pic();

private:
	Ui::BeautyWhoClass *ui;
	QLabel  *label;
	void show_image(QImage *img);
	bool judge();
};

#endif //OOP_FINAL_BEAUTYWHO_H