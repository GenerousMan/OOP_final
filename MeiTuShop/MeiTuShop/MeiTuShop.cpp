#include "MeiTuShop.h"
#include "ui_Meitushop.h"
#include <QFileDialog>
#include <QMessageBox>

MeiTuShop::MeiTuShop(QWidget *parent): 
	QMainWindow(parent)
{
	ui.setupUi(this);
}
void MeiTuShop::openPic()  
{  
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"),".",tr("Image File(*.png *.jpg *.jpeg *.bmp)"));  
    if (fileName.isEmpty())  
    {  
        return;  
    }  
  
    m_srcImage = imread(fileName.toLatin1().data());//读取图片数据  
    if (!m_srcImage.data)  
    {  
        m_isOpenFile = false;  
        QMessageBox box(QMessageBox::Critical, "打开图像", "读取图像文件失败！请重新打开．");  
        box.setStandardButtons(QMessageBox::Ok);  
        box.setButtonText(QMessageBox::Ok, QString("确定"));  
        box.exec();  
        return;  
    }  
    m_isOpenFile = true;//修改打开标志  
}  
  