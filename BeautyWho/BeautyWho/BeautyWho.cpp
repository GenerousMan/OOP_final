#include "BeautyWho.h"
#include <QFileDialog>  
#include <QMessageBox>
#include"./Backend/ImageProcess.h"
#include <string>

enum { OPEN_FILE, GRAY, WHITE, CHANGE_LIGHT, ROTATE, WHITE_BALANCE, NOTHING };// current event
ImageProcessor img;//original picture
bool opened_file = false;
int curr_event = NOTHING;

BeautyWho::BeautyWho(QWidget *parent)
	: QMainWindow(parent)
{
	ui->setupUi(this);
	ui->dockWidget->setMinimumSize(300, 300);

}

void BeautyWho::open_clicked() {
	ui->label_3->setText("");
	if (curr_event != NOTHING) {
		QLabel *label = new QLabel();
		ui->picafter->setWidget(label);
	}
	curr_event = OPEN_FILE;
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
		QByteArray cdata = filename.toLocal8Bit();
		img = cv::imread(std::string(cdata));
		opened_file = true;
		show_image(&img.to_QImage(), 0);
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

bool BeautyWho::judge() {
	if (!opened_file) {
		QMessageBox::information(this,
			tr("Wanning"),
			tr("No images have been opened yet."));
		return false;
	}
	return true;
}

void BeautyWho::gray_clicked() {
	ui->label_3->setText("");
	curr_event = GRAY;
	if (judge()) {
		ImageProcessor n_img = img;
		auto nn_img = n_img.gray();
		show_image(&(nn_img.to_QImage()), 1);
	}
}

void BeautyWho::white_clicked() {
	QString str;
	str = str.fromLocal8Bit("变白程度");
	ui->label_3->setText(str);
	curr_event = WHITE;
	ui->horizontalSlider->setRange(1, 30);
}

void BeautyWho::white_balance_clicked() {
	ui->label_3->setText("");
	curr_event = WHITE_BALANCE;
	if (judge()) {
		ImageProcessor n_img = img;
		auto nn_img = n_img.white_balance();
		show_image(&(nn_img.to_QImage()), 1);
	}
}

void BeautyWho::bright_clicked() {
	QString str;
	str = str.fromLocal8Bit("调节亮度");
	ui->label_3->setText(str);
	curr_event = CHANGE_LIGHT;
	ui->horizontalSlider->setRange(-255, 255);
}

void BeautyWho::rotate_clicked() {
	QString str;
	str = str.fromLocal8Bit("旋转角度");
	ui->label_3->setText(str);
	curr_event = ROTATE;
	ui->horizontalSlider->setRange(0, 359);
}
void BeautyWho::onSliderValueChanged(int i) {
	switch (curr_event) {
	case CHANGE_LIGHT:
		change_light(i);
		break;
	case ROTATE:
		rotate(i);
		break;
	case WHITE:
		white((i + 100) / 100.0);
		break;
	default:
		break;
	}
}
void BeautyWho::change_light(int beta) {
	if (judge()) {
		ImageProcessor n_img = img;
		auto nn_img = n_img.light(beta);
		show_image(&(nn_img.to_QImage()), 1);
	}
}

void BeautyWho::rotate(int angle) {
	if (judge()) {
		ImageProcessor n_img = img;
		auto nn_img = n_img.rotation(angle);
		show_image(&(nn_img.to_QImage()), 1);
	}
}

void BeautyWho::white(double beta) {
	if (judge()) {
		ImageProcessor n_img = img;
		auto nn_img = n_img.whitening(beta);
		show_image(&(nn_img.to_QImage()), 1);
	}
}