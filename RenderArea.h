#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QBrush>
#include <QPen>
#include <QPixmap>
#include <QWidget>
#include "ImageDrawer.h"

class RenderArea : public QWidget
{
  Q_OBJECT

public:

  RenderArea(ImageDrawer *imageDrawer, QWidget *parent = nullptr);
  QSize minimumSizeHint() const override;
  QSize sizeHint() const override;
  void initialize();

protected:

  void paintEvent(QPaintEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void enterEvent(QEvent *event) override;


private:

  QPixmap pixmap;
  ImageDrawer *imageDrawer;

  QSize drawingAreaSize;

  void updatePixmap();


};

#endif // RENDERAREA_H
