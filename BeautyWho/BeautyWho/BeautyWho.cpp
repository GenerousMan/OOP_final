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
		tr("Ñ¡ÔñÍ¼Ïñ"),
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
		label = new QLabel();
		label->setPixmap(QPixmap::fromImage(*img));
		label->resize(QSize(img->width(), img->height()));
		ui->picbefore->setWidget(label);
	}
}

void BeautyWho::show_image(QImage *img) {
	label = new QLabel();
	label->setPixmap(QPixmap::fromImage(*img));
	label->resize(QSize(img->width(), img->height()));
	ui->picafter->setWidget(label);
}

bool BeautyWho::judge() {
	if (!opened_file) {
		QMessageBox::information(this,
			tr("Error"),
			tr("No images have been opened yet."));
		return false;
	}
	return true;
}

void BeautyWho::gray_pic() {
	if (judge()) {
		ImageProcessor n_img = *img;
		auto nn_img = n_img.gray();
		QImage a = nn_img.to_QImage();
		QImage *b = &a;
		show_image(b);
	}
}

void BeautyWho::white_pic() {
	if (judge()) {
		ImageProcessor n_img = *img;
		auto nn_img = n_img.white_balance();
		QImage a = nn_img.to_QImage();
		QImage *b = &a;
		show_image(b);
	}
}