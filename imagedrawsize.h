#ifndef IMAGEDRAWSIZE_H
#define IMAGEDRAWSIZE_H

#include <QDialog>
#include <QCloseEvent>
namespace Ui {
class imageDrawSize;
}

class imageDrawSize : public QDialog
{
    Q_OBJECT

public:
    explicit imageDrawSize(QWidget *parent = nullptr);
    ~imageDrawSize();
    int width;
    int height;

private slots:
    void on_pushButton_clicked();


    void on_imageDrawSize_finished(int result);



private:
    Ui::imageDrawSize *ui;
};

#endif // IMAGEDRAWSIZE_H
