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
	void on_Push_Lv3_clicked();
	void on_Push_Lv4_clicked();
	void onSliderValueChanged(int i);
	
private:
	Ui::BeautyWhoClass *ui;
	void show_image(QImage *img,bool pic) const;
	void change_light(int beta);
	void rotate(int angle);
	bool judge() ;
};

#endif //OOP_FINAL_BEAUTYWHO_H