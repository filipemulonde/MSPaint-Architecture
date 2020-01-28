#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QCheckBox>
#include <QLineEdit>
#include <QLabel>
#include <QColor>
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


  //Menu open
   QAction * NewMenuItem;
    //open Menu Item
   QAction *openMenuItem;
   //Save Menu Item
    QAction * SaveMenuItem;
    //Save As MenuItem
    QAction * SaveAsMenuItem;

  //Pencil items
  QPushButton *pencilButton;

  //Line items
  QPushButton *lineButton;

  //Ruler
  QPushButton *rulerButton;

  //Perspective items
  QPushButton *resetPerspectiveButton;
  QPushButton *addPerspectiveButton;
  QCheckBox *perspectiveEnabledCb;
  bool isSelectingPerspectivePoints = false;

  //Axonometry items
  QLineEdit *alphaLineEdit;
  QLineEdit *betaLineEdit;
  QCheckBox *axonometryEnabledCb;

  //Color
  QPushButton *colorButton;
  QLabel *currentColorLabel;
  QColor currentColor;

  //Gridlines
  QLineEdit *horTickLineEdit;
  QLineEdit *verTickLineEdit;
  QCheckBox *gridlinesEnabledCb;

};
#endif // MAINWINDOW_H
