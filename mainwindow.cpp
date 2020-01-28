#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QColorDialog>
#include <QLabel>
#include <QIntValidator>
#include "imagedrawsize.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent):
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  int width=800, height = 600;
  imageDrawer = new ImageDrawer(width, height);
  QWidget *drawingArea = findChild<QWidget*>("drawingAreaWidget");
  renderArea = new RenderArea(imageDrawer, drawingArea);
  renderArea->initialize();

  pencilButton = findChild<QPushButton*>("pencilButton");
  pencilButton->setCheckable(true);
  pencilButton->setChecked(true);

  lineButton = findChild<QPushButton*>("lineButton");
  lineButton->setCheckable(true);
  lineButton->setChecked(false);

  rulerButton = findChild<QPushButton*>("rulerButton");
  rulerButton->setCheckable(true);
  rulerButton->setChecked(false);

  resetPerspectiveButton = findChild<QPushButton*>("resetPerspectiveButton");
  addPerspectiveButton = findChild<QPushButton*>("addPerspectiveButton");
  perspectiveEnabledCb = findChild<QCheckBox*>("perspectiveEnabledCheckBox");

  alphaLineEdit = findChild<QLineEdit*>("alphaLineEdit");
  betaLineEdit = findChild<QLineEdit*>("betaLineEdit");
  axonometryEnabledCb = findChild<QCheckBox*>("axonometryEnabledCheckBox");

  colorButton = findChild<QPushButton*>("colorButton");
  currentColorLabel = findChild<QLabel*>("currentColorLabel");
  QPalette palette = currentColorLabel->palette();
  palette.setColor(QPalette::Window, Qt::black);
  currentColorLabel->setAutoFillBackground(true);
  currentColorLabel->setPalette(palette);

  horTickLineEdit = findChild<QLineEdit*>("horTickLineEdit");
  horTickLineEdit->setValidator(new QIntValidator(1, width, this));
  verTickLineEdit = findChild<QLineEdit*>("verTickLineEdit");
  verTickLineEdit->setValidator(new QIntValidator(1, height, this));
  gridlinesEnabledCb = findChild<QCheckBox*>("gridlinesEnabledCheckBox");


  NewMenuItem = findChild<QAction *>("actionNew");
  NewMenuItem->setChecked(true);
  NewMenuItem->setCheckable(true);

  // New Menu Item

  connect(NewMenuItem, &QAction::triggered, [&](){


     imageDrawSize  setScrennSize;

     setScrennSize.exec();

     ui->drawingAreaWidget->resize(setScrennSize.width,setScrennSize.height);
     imageDrawer->resize(setScrennSize.width,setScrennSize.height);



  });

  // Open Menu Item

   openMenuItem = findChild<QAction *>("actionOpen");

   connect(openMenuItem, &QAction::triggered, [&](){

       QString file_name = QFileDialog::getOpenFileName(this,"Open File",QDir::homePath());
       QFile file(file_name);

       if(!file.open(QFile::ReadOnly | QFile::Text)){

           QMessageBox::warning(this,"","can not open the file");
           return ;

       }

     //  imageDrawer->open(file_name.toStdString());

   });

    // Save Menu Item


   SaveMenuItem = findChild<QAction *>("actionSave");

   connect(SaveMenuItem, &QAction::triggered, [&](){



   });




  // Simple tool buttons
  connect(pencilButton, &QPushButton::clicked, [&](){
    pencilButton->setChecked(true);
    lineButton->setChecked(false);
    rulerButton->setChecked(false);
    imageDrawer->setActiveTool(ImageDrawer::PENCIL);
  });
  connect(lineButton, &QPushButton::clicked, [&](){
    lineButton->setChecked(true);
    pencilButton->setChecked(false);
    rulerButton->setChecked(false);
    imageDrawer->setActiveTool(ImageDrawer::LINE);
  });
  connect(rulerButton, &QPushButton::clicked, [&](){
    rulerButton->setChecked(true);
    pencilButton->setChecked(false);
    lineButton->setChecked(false);
    imageDrawer->setActiveTool(ImageDrawer::RULER);
  });

  // Perspective drawing items
  connect(addPerspectiveButton, &QPushButton::clicked, [&](){
    if(!isSelectingPerspectivePoints)
    {

       QIcon apply;
       apply.addFile(":/icones/icon/apply-icon.png");
      isSelectingPerspectivePoints = true;
     addPerspectiveButton->setIcon(apply);
      imageDrawer->addPerspectivePoints();
    }
    else
    {
      QIcon add;
      add.addFile(":/icones/icon/add-pngrepo-com.png");
      isSelectingPerspectivePoints = false;
      addPerspectiveButton->setIcon(add);
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

  //Color button
  connect(colorButton, &QPushButton::clicked, [&](){
    QColor color = QColorDialog::getColor(currentColor, this, "Pick a color",  QColorDialog::DontUseNativeDialog);
    QPalette palette = currentColorLabel->palette();
    palette.setColor(QPalette::Window, color);
    currentColorLabel->setAutoFillBackground(true);
    currentColorLabel->setPalette(palette);

    int r, g, b;
    color.getRgb(&r, &g, &b);
    imageDrawer->setActiveColor(r, g, b);
  });

  //Gridlines
  connect(gridlinesEnabledCb, &QCheckBox::stateChanged, [&](int state){

    int horTickPx = horTickLineEdit->text().toInt();
    int verTickPx = verTickLineEdit->text().toInt();

    switch(state)
    {
    case Qt::Checked:
      imageDrawer->setGridLines(horTickPx, verTickPx);
      imageDrawer->setGridLinesVisible(true);
      renderArea->update();
      break;
    case Qt::Unchecked:
      imageDrawer->setGridLinesVisible(false);
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
