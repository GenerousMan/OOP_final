#include "BeautyWho.h"
#include <QFileDialog>  
#include <QMessageBox>

BeautyWho::BeautyWho(QWidget *parent)
	: QMainWindow(parent)
{
	ui->setupUi(this);
}
void BeautyWho::open_pic() {
	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		tr("ѡ��ͼ��"),
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
	if (filename.isEmpty())
	{
		return;
	}
	else
	{
		QImage* img = new QImage;

		if (!(img->load(filename))) //����ͼ��
		{
			QMessageBox::information(this,
				tr("��ͼ��ʧ��"),
				tr("��ͼ��ʧ��!"));
			delete img;
			return;
		}
		label = new QLabel();
		label->setPixmap(QPixmap::fromImage(*img));
		label->resize(QSize(img->width(), img->height()));
		ui->picbefore->setWidget(label);
	}
}