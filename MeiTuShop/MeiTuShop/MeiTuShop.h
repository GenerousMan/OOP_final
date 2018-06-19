#ifndef MEITUSHOP_H
#define MEITUSHOP_H

#include <QtWidgets/QMainWindow>
#include "ui_MeiTuShop.h"
#include <QImage>

class MeiTuShop : public QMainWindow
{
	Q_OBJECT

public:
	MeiTuShop(QWidget *parent = Q_NULLPTR);
	~MeituShop();

private slots:
	void LvJing1();
	void LvJing2();
	void LvJing3();
	void LvJing4();
	void face();
	void openPic();
	
private:
	Ui::MeiTuShopClass ui;
	QImage old_pic;
	QImage new_pic;
};
#endif