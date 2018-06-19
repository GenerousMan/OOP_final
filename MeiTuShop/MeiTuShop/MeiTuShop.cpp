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
  
    m_srcImage = imread(fileName.toLatin1().data());//��ȡͼƬ����  
    if (!m_srcImage.data)  
    {  
        m_isOpenFile = false;  
        QMessageBox box(QMessageBox::Critical, "��ͼ��", "��ȡͼ���ļ�ʧ�ܣ������´򿪣�");  
        box.setStandardButtons(QMessageBox::Ok);  
        box.setButtonText(QMessageBox::Ok, QString("ȷ��"));  
        box.exec();  
        return;  
    }  
    m_isOpenFile = true;//�޸Ĵ򿪱�־  
}  
  