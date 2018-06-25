#include "BeautyWho.h"
#include <QFileDialog>  
#include <QMessageBox>
#include"./Backend/ImageProcess.h"
#include <string>

enum { OPEN_FILE, GRAY, WHITE, CHANGE_LIGHT, ROTATE, WHITE_BALANCE, 
	NOTHING,HUE, CHANGE_PIC,BUFFERING,ENHANCE,GAMMA,SATURATION};// current event
enum {LEFT,RIGHT};
ImageProcessor img;
ImageProcessor nn_img;
bool opened_file = false;

int curr_event = NOTHING;

BeautyWho::BeautyWho(QWidget *parent)
	: QMainWindow(parent)
{
	ui->setupUi(this);
	ui->dockWidget->setMinimumSize(300, 200);

}

void BeautyWho::hide_widget() {
	ui->dockWidget->hide();
}

void BeautyWho::show_widget(const char* a) {
	ui->dockWidget->show();
	QString str;
	str = str.fromLocal8Bit(a);
	ui->label_3->setText(str);
}

void BeautyWho::open_clicked() {
	hide_widget();
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
		show_image(&img.to_QImage(), LEFT);
		show_image(&img.to_QImage(), RIGHT);
	}
}

void BeautyWho::show_image(QImage *img, bool pic)const {
	QLabel *label = new QLabel();
	label->setPixmap(QPixmap::fromImage(*img));
	label->resize(QSize(img->width(), img->height()));
	if (pic==RIGHT) 
		ui->picafter->setWidget(label);
	else
		ui->picbefore->setWidget(label);
}

bool BeautyWho::judge() {
	if (!opened_file) {
		QMessageBox::information(this,
			tr("出现错误"),
			tr("您还没有打开图片"));
		return false;
	}
	return true;
}

void BeautyWho::onSliderValueChanged(int i) {
	if (!ui->dockWidget->isVisible())
		return;
	switch (curr_event) {
	case CHANGE_LIGHT:
		change_light(i);
		break;
	case ROTATE:
		rotate(i);
		break;
	case WHITE:
		white((i + 1000) / 1000.0);
		break;
	case HUE:
		hue(i);
		break;
	case BUFFERING:
		buffering(i);
		break;
	case SATURATION:
		saturation(i);
		break;
	default:
		break;
	}
}

void BeautyWho::gamma_clicked() {
	hide_widget();
	curr_event = GAMMA;
	if (judge()) {
		ImageProcessor n_img = img;
		nn_img = n_img.gamma_adjust();
		show_image(&(nn_img.to_QImage()), RIGHT);
	}
}

void BeautyWho::enhance_clicked() {
	hide_widget();
	curr_event = ENHANCE;
	if (judge()) {
		ImageProcessor n_img = img;
		nn_img = n_img.enhance();
		show_image(&(nn_img.to_QImage()), RIGHT);
	}
}

void BeautyWho::gray_clicked() {
	hide_widget();
	curr_event = GRAY;
	if (judge()) {
		ImageProcessor n_img = img;
		nn_img = n_img.gray();
		show_image(&(nn_img.to_QImage()), RIGHT);
	}
}

void BeautyWho::white_balance_clicked() {
	hide_widget();
	curr_event = WHITE_BALANCE;
	if (judge()) {
		ImageProcessor n_img = img;
		nn_img = n_img.white_balance();
		show_image(&(nn_img.to_QImage()), RIGHT);
	}
}

void BeautyWho::white_clicked() {
	if (judge()) {
		show_widget("变白程度");
		curr_event = WHITE;
		ui->horizontalSlider->setRange(1, 280);
	}
	
}

void BeautyWho::bright_clicked() {
	if (judge()) {
		show_widget("调节亮度");
		curr_event = CHANGE_LIGHT;
		ui->horizontalSlider->setRange(-255, 255);
	}
	
}

void BeautyWho::rotate_clicked() {
	if (judge()){
		show_widget("旋转角度");
		curr_event = ROTATE;
		ui->horizontalSlider->setRange(0, 359);
	}
}

void BeautyWho::hue_clicked() {
	if (judge()) {
		show_widget("色彩调整");
		curr_event = HUE;
		ui->horizontalSlider->setRange(0, 120);
	}
}

void BeautyWho::buffering_clicked() {
	if (judge()) {
		show_widget("磨皮程度");
		curr_event = BUFFERING;
		ui->horizontalSlider->setRange(4,11);
	}
}

void BeautyWho::change_pic() {
	hide_widget();
	curr_event = CHANGE_PIC;
	if (judge()) {
		img = nn_img;
		show_image(&(nn_img.to_QImage()), LEFT);
	}
}

void BeautyWho::change_light(int beta) {
	
		ImageProcessor n_img = img;
		nn_img = n_img.light(beta);
		show_image(&(nn_img.to_QImage()), RIGHT);
	
}

void BeautyWho::rotate(int angle) {
	
		ImageProcessor n_img = img;
		nn_img = n_img.rotation(angle);
		show_image(&(nn_img.to_QImage()), RIGHT);
	
}

void BeautyWho::white(double beta) {
	
		ImageProcessor n_img = img;
		nn_img = n_img.whitening(beta);
		show_image(&(nn_img.to_QImage()), RIGHT);
	
}

void BeautyWho::buffering(int i) {
		ImageProcessor n_img = img;
		nn_img = n_img.buffing(i, i / 3);
		show_image(&(nn_img.to_QImage()), RIGHT);
}

void BeautyWho::hue(int a) {
		ImageProcessor n_img = img;
		nn_img = n_img.hue(a);
		show_image(&(nn_img.to_QImage()), RIGHT);
}

void BeautyWho::saturation(int a) {
	ImageProcessor n_img = img;
	nn_img = n_img.saturation(a);
	show_image(&(nn_img.to_QImage()), RIGHT);
}

void BeautyWho::saturation_clicked() {
	if (judge()) {
		show_widget("");
		curr_event = SATURATION;
		ui->horizontalSlider->setRange(0, 120);
	}
}

void BeautyWho::setArrow() {
	QPixmap pixmap("pic.png");
	ui->label_4->setPixmap(pixmap);
	ui->label_4->show();
}