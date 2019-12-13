#include "LineTool.h"

LineTool::LineTool(cv::Mat &image_layer, cv::Mat &preview_layer, const cv::Vec3b &color):
  Tool(image_layer, preview_layer),
  color_(color),
  mouse_clicked_(false)
{
}

void LineTool::mouse_move(const cv::Point &position)
{
  if(mouse_clicked_)
  {
    image_layer_.copyTo(preview_layer_);
    cv::line(preview_layer_, lastClickPoint_, position, color_);
  }
}

void LineTool::mouse_press(const cv::Point &position)
{
  mouse_clicked_ = true;
  //preview_layer_.at<cv::Vec3b>(position) = color_;
  lastClickPoint_ = position;
}

void LineTool::mouse_release(const cv::Point& /*position*/)
{
  mouse_clicked_ = false;
  preview_layer_.copyTo(image_layer_);
}

void LineTool::setColor(const cv::Vec3b &color)
{
  color_ = color;
}
