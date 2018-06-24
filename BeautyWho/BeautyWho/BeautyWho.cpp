#include "BeautyWho.h"
#include <QFileDialog>  
#include <QMessageBox>
#include"./Backend/ImageProcess.h"

QImage *img = new QImage;
bool opened_file = false;

BeautyWho::BeautyWho(QWidget *parent)
	: QMainWindow(parent)
{
	ui->setupUi(this);
}

void BeautyWho::open_pic() {
	QString filename;
	filename = QFileDialog::getOpenFileName(this,
		tr("choose an image"),
		"",
		tr("Images (*.png *.bmp *.jpg *.tif *.GIF )"));
	if (filename.isEmpty())
	{
		return;
	}
	else
	{

		if (!(img->load(filename))) //¼ÓÔØÍ¼Ïñ
		{
			QMessageBox::information(this,
				tr("´ò¿ªÍ¼ÏñÊ§°Ü"),
				tr("´ò¿ªÍ¼ÏñÊ§°Ü!"));
			delete img;
			return;
		}
		opened_file = true;
		show_image(img, false);
	}
}

void BeautyWho::show_image(QImage *img, bool pic)const {
	QLabel *label = new QLabel();
	label->setPixmap(QPixmap::fromImage(*img));
	label->resize(QSize(img->width(), img->height()));
	if (pic)
		ui->picafter->setWidget(label);
	else
		ui->picbefore->setWidget(label);
}

bool BeautyWho::judge()  {
	if (!opened_file) {
		QMessageBox::information(this,
			tr("Wanning"),
			tr("No images have been opened yet."));
		return false;
	}
	return true;
}

void BeautyWho::gray_pic() {
	if (judge()) {
		ImageProcessor n_img = *img;
		auto nn_img = n_img.gray();
		show_image(&(nn_img.to_QImage()), true);
	}
}

void BeautyWho::white_pic() {
	if (judge()) {
		ImageProcessor n_img = *img;
		auto nn_img = n_img.hue(-50);
		QLabel *l = new QLabel();
		l->setPixmap(QPixmap::fromImage(nn_img.to_QImage()));
		l->show();
	}
}
