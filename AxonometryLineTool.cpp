#include "AxonometryLineTool.h"


AxonometryLineTool::AxonometryLineTool(
    cv::Mat &image_layer, cv::Mat &preview_layer,
    const cv::Vec3b &color, const std::vector<double> &axonometryAngles):
  PerspectiveLineTool(image_layer, preview_layer, color, emptyVec),
  axonometryAngles_(axonometryAngles)
{

}

void AxonometryLineTool::mouse_press(const cv::Point &position)
{
  PerspectiveLineTool::mouse_press(position);

  for(double angle: axonometryAngles_)
  {
    double angle_rad = angle*M_PI/180.0;
    cv::Point2d vec(10 * std::cos(angle_rad), 10 * std::sin(angle_rad));
    dPerspectivePoints.push_back(position + cv::Point(vec));
  }

}

void AxonometryLineTool::mouse_move(const cv::Point &position)
{
  PerspectiveLineTool::mouse_move(position);
}
