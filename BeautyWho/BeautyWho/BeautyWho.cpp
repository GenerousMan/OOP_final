#include "BeautyWho.h"
#include <QFileDialog>  
#include <QMessageBox>
#include"./Backend/ImageProcess.h"

#define OPEN_FILE    0
#define GRAY         1
#define WHITE        2
#define CHNAGE_LIGHT 3
#define ROTATE       4

QImage img = QImage();
bool opened_file = false;
int curr_event = OPEN_FILE;
BeautyWho::BeautyWho(QWidget *parent)
	: QMainWindow(parent)
{
	//ui->dockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
	//ui->dockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
	//ui->dockWidget->setMaximumSize(300, 3000);
	ui->setupUi(this);
}

void BeautyWho::open_clicked() {
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
		//ImageProcessor temp_img = cv::imread(filename.toStdString());
		ImageProcessor* temp_img = new ImageProcessor( cv::imread(filename.toStdString()));
		//img = temp_img.to_pQImage();
		img = temp_img->to_QImage();
		if(false)
		//if (!(img->load(filename))) //加载图像
		{
			QMessageBox::information(this,
				tr("打开图像失败"),
				tr("打开图像失败!"));
			//delete img;
			return;
		}
		opened_file = true;
		show_image(&img, 0);
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

void BeautyWho::gray_clicked() {
	curr_event = GRAY;
	if (judge()) {
		ImageProcessor n_img = img;
		auto nn_img = n_img.gray();
		show_image(&(nn_img.to_QImage()), 1);
	}
}

void BeautyWho::white_clicked() {
	curr_event = WHITE;
	if (judge()) {
		ImageProcessor n_img = img;
		auto nn_img = n_img.hue(-50);
		show_image(&(nn_img.to_QImage()), 1);
	}
}

void BeautyWho::bright_clicked() {
	curr_event = CHNAGE_LIGHT;
	ui->horizontalSlider->setRange(0, 255);
}

void BeautyWho::rotate_clicked() {
	curr_event = ROTATE;
	ui->horizontalSlider->setRange(0, 359);
}
void BeautyWho::onSliderValueChanged(int i) {
	switch (curr_event) {
		case (CHNAGE_LIGHT):
			change_light(i);
			break;
		case (ROTATE):
			rotate(i);
			break;
		default:
			break;
	}
}
void BeautyWho::change_light(int beta){
	if (judge()){
		ImageProcessor n_img = img;
		auto nn_img = n_img.light(beta);
		show_image(&(nn_img.to_QImage()),1); 
	}
}

void BeautyWho::rotate(int angle) {
	if (judge()) {
		ImageProcessor n_img = img;
		auto nn_img = n_img.rotation(angle);
		show_image(&(nn_img.to_QImage()), 1);
	}
}
