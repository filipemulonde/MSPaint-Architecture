#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent):
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  imageDrawer = new ImageDrawer(1280, 1920);
  QWidget *drawingArea = findChild<QWidget*>("drawingAreaWidget");
  renderArea = new RenderArea(imageDrawer, drawingArea);
  renderArea->initialize();

  pencilButton = findChild<QPushButton*>("pencilButton");
  pencilButton->setCheckable(true);
  pencilButton->setChecked(true);

  lineButton = findChild<QPushButton*>("lineButton");
  lineButton->setCheckable(true);
  lineButton->setChecked(false);

  resetPerspectiveButton = findChild<QPushButton*>("resetPerspectiveButton");
  addPerspectiveButton = findChild<QPushButton*>("addPerspectiveButton");
  perspectiveEnabledCb = findChild<QCheckBox*>("perspectiveEnabledCheckBox");

  alphaLineEdit = findChild<QLineEdit*>("alphaLineEdit");
  betaLineEdit = findChild<QLineEdit*>("betaLineEdit");
  axonometryEnabledCb = findChild<QCheckBox*>("axonometryEnabledCheckBox");


  // Simple tool buttons
  connect(pencilButton, &QPushButton::clicked, [&](){
    pencilButton->setChecked(true);
    lineButton->setChecked(false);
    imageDrawer->setActiveTool(ImageDrawer::PENCIL);
  });
  connect(lineButton, &QPushButton::clicked, [&](){
    lineButton->setChecked(true);
    pencilButton->setChecked(false);
    imageDrawer->setActiveTool(ImageDrawer::LINE);
  });


  // Perspective drawing items
  connect(addPerspectiveButton, &QPushButton::clicked, [&](){
    if(!isSelectingPerspectivePoints)
    {
      isSelectingPerspectivePoints = true;
      addPerspectiveButton->setText("Apply");
      imageDrawer->addPerspectivePoints();
    }
    else
    {
      isSelectingPerspectivePoints = false;
      addPerspectiveButton->setText("Add");
      imageDrawer->applyPerspectivePoints();
    }
  });
  connect(resetPerspectiveButton, &QPushButton::clicked, [&](){
    imageDrawer->resetPerspectivePoints();
    renderArea->update();
  });
  connect(perspectiveEnabledCb, &QCheckBox::stateChanged, [&](int state){
    std::cout << "perspectiveCb_handler" << std::endl;
    switch(state)
    {
    case Qt::Checked:
      std::cout << "pcb_checked" << std::endl;
      imageDrawer->setActiveMode(ImageDrawer::work_mode_t::PERSPECTIVE);
      renderArea->update();
      break;
    case Qt::Unchecked:
      std::cout << "pcb_unchecked" << std::endl;
      imageDrawer->setActiveMode(ImageDrawer::work_mode_t::NORMAL);
      renderArea->update();
      break;
    }
  });

  //Axonometry items
  connect(axonometryEnabledCb, &QCheckBox::stateChanged, [&](int state){
    std::cout << "axonometryCb_handler" << std::endl;

    switch(state)
    {
    case Qt::Checked:
      //TODO: check if angles are valid (real numbers)
      imageDrawer->setAxonometryAngles(alphaLineEdit->text().toDouble(),
                                       betaLineEdit->text().toDouble());
      imageDrawer->setActiveMode(ImageDrawer::work_mode_t::AXONOMETRY);
      renderArea->update();
      break;
    case Qt::Unchecked:
      imageDrawer->setActiveMode(ImageDrawer::work_mode_t::NORMAL);
      renderArea->update();
      break;
    }

  });
}

MainWindow::~MainWindow()
{
  delete renderArea;
  delete ui;
}
