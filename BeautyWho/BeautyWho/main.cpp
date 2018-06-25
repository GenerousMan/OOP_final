#pragma execution_character_set("utf-8")

#include "BeautyWho.h"
#include <QtWidgets/QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	

	
	BeautyWho w;
	w.hide_widget();
	w.show();
	w.setArrow();

	return a.exec();
}
