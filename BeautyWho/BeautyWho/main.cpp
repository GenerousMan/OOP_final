#include "BeautyWho.h"
#include <QtextCodec>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	
	QApplication a(argc, argv);
	BeautyWho w;
	w.hide_widget();
	w.show();
	w.setArrow();
	return a.exec();
}
