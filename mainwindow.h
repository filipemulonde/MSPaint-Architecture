#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include "ImageDrawer.h"
#include "RenderArea.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:

  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:

  Ui::MainWindow *ui;
  RenderArea *renderArea;
  ImageDrawer *imageDrawer;


  //Pencil items
  QPushButton *pencilButton;

  //Line items
  QPushButton *lineButton;

  //Perspective items
  QPushButton *resetPerspectiveButton;
  QPushButton *addPerspectiveButton;
  QCheckBox *perspectiveEnabledCb;
  bool isSelectingPerspectivePoints = false;

  //Axonometry items
  QLineEdit *alphaLineEdit;
  QLineEdit *betaLineEdit;
  QCheckBox *axonometryEnabledCb;

};
#endif // MAINWINDOW_H
