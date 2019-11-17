#include "PencilTool.h"

PencilTool::PencilTool(cv::Mat &image_layer, cv::Mat &preview_layer, const cv::Vec3b &color):
  Tool(image_layer, preview_layer),
  color_(color),
  mouse_clicked_(false)
{
}

void PencilTool::mouse_move(const cv::Point &position)
{
  if(mouse_clicked_)
  {
    cv::line(image_layer_, lastPosition_, position, color_);
    image_layer_.copyTo(preview_layer_);
    lastPosition_ = position;
  }
}

void PencilTool::mouse_press(const cv::Point &position)
{
  mouse_clicked_ = true;
  image_layer_.at<cv::Vec3b>(position) = color_;
  lastPosition_ = position;
}

void PencilTool::mouse_release(const cv::Point& /*position*/)
{
  mouse_clicked_ = false;
}

void PencilTool::setColor(const cv::Vec3b &color)
{
  color_ = color;
}
