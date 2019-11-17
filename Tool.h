#ifndef TOOL_H
#define TOOL_H

#include <opencv2/opencv.hpp>

class Tool
{

public:

  Tool(cv::Mat &image_layer, cv::Mat &preview_layer):
    image_layer_(image_layer), preview_layer_(preview_layer){}

  virtual ~Tool() = default;
  virtual void mouse_move(const cv::Point &position);
  virtual void mouse_press(const cv::Point &position);
  virtual void mouse_release(const cv::Point &position);

protected:

  cv::Mat &image_layer_;
  cv::Mat &preview_layer_;

};


#endif // TOOL_H
