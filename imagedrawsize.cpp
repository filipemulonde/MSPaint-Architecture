#include "imagedrawsize.h"
#include "ui_imagedrawsize.h"


#include <QMessageBox>

imageDrawSize::imageDrawSize(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::imageDrawSize)
{
    ui->setupUi(this);
    ui->widthLineEdit->setValidator( new QDoubleValidator(0, 100, 2, this) );
    ui->heigthLineEdit->setValidator( new QDoubleValidator(0, 100, 2, this) );
    //setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
}


imageDrawSize::~imageDrawSize()
{
    delete ui;
}

void imageDrawSize::on_pushButton_clicked()
{


     QString widthStr = ui->widthLineEdit->text();
     QString heightStr = ui->heigthLineEdit->text();

     width = widthStr.toInt();
     height = heightStr.toInt();

     if(widthStr.isEmpty() || heightStr.isEmpty() ){

         width =  1200;
         height = 1200;
     }
    hide();

}




void imageDrawSize::on_imageDrawSize_finished(int result)
{
    width =  1200;
    height = 1200;
}


