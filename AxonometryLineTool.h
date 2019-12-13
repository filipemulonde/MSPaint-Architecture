#ifndef AXONOMETRYLINETOOL_H
#define AXONOMETRYLINETOOL_H

#include "PerspectiveLineTool.h"

class AxonometryLineTool: public PerspectiveLineTool
{

public:

  AxonometryLineTool(cv::Mat &image_layer, cv::Mat &preview_layer, const cv::Vec3b &color,
                     const std::vector<double> &axonometryAngles);

  void mouse_press(const cv::Point &position) override;
  void mouse_move(const cv::Point &position) override;

private:

  std::vector<cv::Point> emptyVec;
  const std::vector<double> &axonometryAngles_;

};




#endif // AXONOMETRYLINETOOL_H
