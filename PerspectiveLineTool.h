#ifndef PERSPECTIVELINETOOL_H
#define PERSPECTIVELINETOOL_H

#include <opencv2/opencv.hpp>
#include "LineTool.h"

class PerspectiveLineTool: public LineTool
{

public:

  PerspectiveLineTool(cv::Mat &image_layer, cv::Mat &preview_layer, const cv::Vec3b &color,
                      const std::vector<cv::Point> &perspectivePoints);
  void mouse_press(const cv::Point &position) override;
  void mouse_move(const cv::Point &position) override;

protected:

  const std::vector<cv::Point> &perspectivePoints_;
  std::vector<cv::Point> dPerspectivePoints;

};
#endif // PERSPECTIVELINETOOL_H
