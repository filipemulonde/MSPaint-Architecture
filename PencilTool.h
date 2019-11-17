#ifndef LINETOOL_H
#define LINETOOL_H

#include <Tool.h>
#include <opencv2/opencv.hpp>

class PencilTool: public Tool
{

public:

  PencilTool(cv::Mat &image_layer, cv::Mat &preview_layer, const cv::Vec3b &color);
  void mouse_move(const cv::Point &position) override;
  void mouse_press(const cv::Point &position) override;
  void mouse_release(const cv::Point &position) override;

  void setColor(const cv::Vec3b &color);

private:

  cv::Point lastPosition_;
  cv::Vec3b color_;
  bool mouse_clicked_;

};

#endif // LINETOOL_H
