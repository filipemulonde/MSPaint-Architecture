#include "RenderArea.h"

#include <QPainter>
#include <QMouseEvent>
#include <QImage>
#include <QColor>
#include <opencv2/opencv.hpp>

#include <iostream>

RenderArea::RenderArea(ImageDrawer* imageDrawer, QWidget *parent)
  : QWidget(parent)
{
  this->imageDrawer = imageDrawer;
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
  updatePixmap();
  setMouseTracking(true);
}

QSize RenderArea::minimumSizeHint() const
{
  return QSize(800, 600);
}

QSize RenderArea::sizeHint() const
{
  return QSize(800, 600);
}

void RenderArea::initialize()
{
//  QSize windowSize = QSize(800, 600); //size();
//  QSize frameSize(imageDrawer->getWidth(), imageDrawer->getHeight());
//  frameSize.scale(windowSize, Qt::KeepAspectRatio);
//  drawingAreaSize = frameSize;

//  std::cout << "windowSize = " << windowSize.width() << ", " << windowSize.height() << std::endl;
//  std::cout << "drawingAreaSize = " << drawingAreaSize.width() << ", " << drawingAreaSize.height() << std::endl;
//  std::cout << "frameSize = " << imageDrawer->getWidth() << ", " << imageDrawer->getHeight() << std::endl;

}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
  updatePixmap();
  QPainter painter(this);
  painter.drawPixmap(0, 0, pixmap);
}

void RenderArea::mouseMoveEvent(QMouseEvent *event)
{

//  std::cout << "event.xy = " << event->x() << ", " << event->y() << std::endl;
//  double xScale1 = drawingAreaSize.width() / 800.0;
//  double yScale1 = drawingAreaSize.height() / 600.0;
//  double x = xScale1 * event->x();
//  double y = yScale1 * event->y();
//  std::cout << "scale1.xy = " << x << ", " << y << std::endl;
//  double xScale = imageDrawer->getWidth() / drawingAreaSize.width();
//  double yScale = imageDrawer->getHeight() / drawingAreaSize.height();
//  std::cout << "scale2.xy = " << xScale*x << ", " << yScale*y << std::endl;
//imageDrawer->mouse_move(int(xScale * x), int(yScale * y));

  imageDrawer->mouse_move(event->x(), event->y());
  update();
}

void RenderArea::mousePressEvent(QMouseEvent *event)
{
//  double xScale1 = drawingAreaSize.width() / 800.0;
//  double yScale1 = drawingAreaSize.height() / 600.0;
//  double xScale = imageDrawer->getWidth() / drawingAreaSize.width();
//  double yScale = imageDrawer->getHeight() / drawingAreaSize.height();
//  //imageDrawer->mouse_press(int(xScale * event->x()), int(yScale * event->y()));
//  imageDrawer->mouse_move(int(xScale1 * xScale * event->x()), int(yScale1 * yScale * event->y()));

  imageDrawer->mouse_press(event->x(), event->y());

  update();
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event)
{
//  double xScale1 = drawingAreaSize.width() / 800.0;
//  double yScale1 = drawingAreaSize.height() / 600.0;
//  double xScale = imageDrawer->getWidth() / drawingAreaSize.width();
//  double yScale = imageDrawer->getHeight() / drawingAreaSize.height();
//  //imageDrawer->mouse_release(int(xScale * event->x()), int(yScale * event->y()));
//  imageDrawer->mouse_move(int(xScale1 * xScale * event->x()), int(yScale1 * yScale * event->y()));

  imageDrawer->mouse_release(event->x(), event->y());

  update();
}

void RenderArea::enterEvent(QEvent* /*event*/)
{
  setCursor(QCursor(Qt::CrossCursor));
}

void RenderArea::updatePixmap()
{
  cv::Mat frame = imageDrawer->getFrame();

//  QSize windowSize = QSize(800, 600);
//  QSize frameSize(frame.size[1], frame.size[0]);

//  frameSize.scale(windowSize, Qt::KeepAspectRatio);

//  cv::Mat resizedFrame;
//  cv::resize(frame, resizedFrame, cv::Size(frameSize.height(), frameSize.width()));


  pixmap = QPixmap::fromImage(QImage((unsigned char*) frame.data, frame.cols, frame.rows, QImage::Format_RGB888));

//  cv::Mat result(windowSize.height(), windowSize.width(), CV_8UC3, cv::Scalar(0, 255, 0));
//  resizedFrame.copyTo(result(cv::Rect(0,0,resizedFrame.cols, resizedFrame.rows)));

//  pixmap = QPixmap::fromImage(QImage((unsigned char*) result.data, result.cols, result.rows, QImage::Format_RGB888));

}







