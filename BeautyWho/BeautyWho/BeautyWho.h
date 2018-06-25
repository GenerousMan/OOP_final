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
	void bright_clicked();
	void rotate_clicked();
	void open_clicked();
	void gray_clicked();
	void white_clicked();
	void white_balance_clicked();
	void onSliderValueChanged(int i);
	
private:
	Ui::BeautyWhoClass *ui;
	void show_image(QImage *img,bool pic) const;
	void change_light(int beta);
	void rotate(int angle);
	bool judge() ;
	void white(double beta);
};

#endif //OOP_FINAL_BEAUTYWHO_H