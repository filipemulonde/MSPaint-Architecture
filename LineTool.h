#ifndef LINETOOL_H
#define LINETOOL_H

#include <Tool.h>
#include <opencv2/opencv.hpp>

class LineTool: public Tool
{

public:

  LineTool(cv::Mat &image_layer, cv::Mat &preview_layer, const cv::Vec3b &color);
  void mouse_move(const cv::Point &position) override;
  void mouse_press(const cv::Point &position) override;
  void mouse_release(const cv::Point &position) override;

  void setColor(const cv::Vec3b &color);

protected:

  cv::Point lastClickPoint_;
  cv::Vec3b color_;
  bool mouse_clicked_;

};



#endif // LINETOOL_H
