#include "BeautyWho.h"
#include <QtextCodec>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	BeautyWho w;
	w.show();
	w.hide_widget();
	return a.exec();
}
