#include "RulerTool.h"
#include <QDebug>

RulerTool::RulerTool(cv::Mat &image_layer, cv::Mat &preview_layer, const cv::Vec3b &color):
  Tool(image_layer, preview_layer),
  color_(25, 170, 170),
  numClicks_(0)
{
}

void RulerTool::mouse_move(const cv::Point &position)
{
  qDebug() << "mouse_move " << numClicks_;
  if(numClicks_ == 2)
  {
    cv::Point d = getPerpendicularVector(a, b, position);
    cv::Point a2 = a + d;
    cv::Point b2 = b + d;

    image_layer_.copyTo(preview_layer_);
    cv::line(preview_layer_, a, a2, color_);
    cv::line(preview_layer_, b, b2, color_);
    cv::line(preview_layer_, a2, b2, color_);

    cv::Point avg = (a2 + b2) / 2;
    double length = abs(cv::norm(b - a));
    QString lengthStr = QString::number(length, 'f', 2);
    cv::putText(preview_layer_, lengthStr.toStdString(), avg, cv::FONT_HERSHEY_COMPLEX_SMALL, 0.5, color_);
  }
}

void RulerTool::mouse_press(const cv::Point &position)
{
  qDebug() << "mouse_press " << numClicks_;
  numClicks_++;
  if(numClicks_ <= 2)
  {
    preview_layer_.at<cv::Vec3b>(position) = cv::Vec3b(0, 0, 255);

    if(numClicks_ == 1)
      a = position;
    else if (numClicks_ == 2)
      b = position;
  }
}

void RulerTool::mouse_release(const cv::Point& position)
{
  qDebug() << "mouse_release " << numClicks_;
  if(numClicks_ == 3)
  {
    preview_layer_.copyTo(image_layer_);
    numClicks_ = 0;
  }
}

void RulerTool::setColor(const cv::Vec3b &color)
{
  color_ = color;
}

cv::Point RulerTool::getPerpendicularVector(const cv::Point &A, const cv::Point &B, const cv::Point &C)
{
  cv::Point2d v1 = C - A;
  cv::Point2d v2 = B - A;
  v2 = v2 / cv::norm(v2);

  double dp = v1.dot(v2);
  double length = dp / cv::norm(v2);
  cv::Point2d v3 = v2 * length;

  cv::Point H = A + cv::Point(v3);

  cv::Point d = C - H;

  return d;
}
