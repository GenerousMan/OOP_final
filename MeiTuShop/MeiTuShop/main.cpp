#include "MeiTuShop.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MeiTuShop w;
	w.show();
	return a.exec();
}
