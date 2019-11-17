#include "RenderArea.h"

#include <QPainter>
#include <QMouseEvent>
#include <QImage>
#include <QColor>
#include <opencv2/opencv.hpp>

RenderArea::RenderArea(ImageDrawer* imageDrawer, QWidget *parent)
  : QWidget(parent)
{
  this->imageDrawer = imageDrawer;
  setBackgroundRole(QPalette::Base);
  setAutoFillBackground(true);
  updatePixmap();
}

QSize RenderArea::minimumSizeHint() const
{
  return QSize(800, 600);
}

QSize RenderArea::sizeHint() const
{
  return QSize(800, 600);
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
  QPainter painter(this);
  painter.drawPixmap(0, 0, pixmap);
}

void RenderArea::mouseMoveEvent(QMouseEvent *event)
{
  imageDrawer->mouse_move(event->x(), event->y());
  updatePixmap();
}

void RenderArea::mousePressEvent(QMouseEvent *event)
{
  imageDrawer->mouse_press(event->x(), event->y());
  updatePixmap();
}

void RenderArea::mouseReleaseEvent(QMouseEvent *event)
{
  imageDrawer->mouse_release(event->x(), event->y());
  updatePixmap();
}

void RenderArea::enterEvent(QEvent* /*event*/)
{
  setCursor(QCursor(Qt::CrossCursor));
}

void RenderArea::updatePixmap()
{
  cv::Mat mat = imageDrawer->getFrame();
  pixmap = QPixmap::fromImage(QImage((unsigned char*) mat.data, mat.cols, mat.rows, QImage::Format_RGB888));
  update();
}
