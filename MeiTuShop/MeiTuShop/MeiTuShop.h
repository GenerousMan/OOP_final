#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MeiTuShop.h"

class MeiTuShop : public QMainWindow
{
	Q_OBJECT

public:
	MeiTuShop(QWidget *parent = Q_NULLPTR);

private:
	Ui::MeiTuShopClass ui;
};
