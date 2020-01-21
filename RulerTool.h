#ifndef RULERTOOL_H
#define RULERTOOL_H

#include <Tool.h>
#include <opencv2/opencv.hpp>

class RulerTool: public Tool
{

public:

  RulerTool(cv::Mat &image_layer, cv::Mat &preview_layer, const cv::Vec3b &color);
  void mouse_move(const cv::Point &position) override;
  void mouse_press(const cv::Point &position) override;
  void mouse_release(const cv::Point &position) override;

  void setColor(const cv::Vec3b &color);

protected:

  cv::Point a, b;
  int numClicks_;

  cv::Vec3b color_;

  cv::Point getPerpendicularVector(const cv::Point &LA, const cv::Point &LB, const cv::Point &C);

};


#endif // RULERTOOL_H
