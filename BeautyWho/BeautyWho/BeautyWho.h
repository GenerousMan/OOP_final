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
	void hide_widget();
	void show_widget(const char* a);
	void setArrow();

private slots:
	void bright_clicked();
	void rotate_clicked();
	void open_clicked();
	void hue_clicked();
	void gray_clicked();
	void white_clicked();
	void buffering_clicked();
	void white_balance_clicked();
	void onSliderValueChanged(int i);
	void change_pic();
	void enhance_clicked();
	void gamma_clicked();
	void saturation_clicked();

private:
	Ui::BeautyWhoClass *ui;
	void show_image(QImage *img,bool pic) const;
	void change_light(int beta);
	void rotate(int angle);
	bool judge() ;
	void white(double beta);
	void hue(int a);
	void buffering(int a);
	void saturation(int a);
};

#endif //OOP_FINAL_BEAUTYWHO_H