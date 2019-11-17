#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent):
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  imageDrawer = new ImageDrawer(1920, 1080);
  QWidget *drawingArea = findChild<QWidget*>("drawingAreaWidget");
  renderArea = new RenderArea(imageDrawer, drawingArea);
}

MainWindow::~MainWindow()
{
  delete renderArea;
  delete ui;
}
