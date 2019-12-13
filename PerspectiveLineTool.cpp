#include "PerspectiveLineTool.h"
#include <algorithm>
#include <math.h>

PerspectiveLineTool::PerspectiveLineTool(
    cv::Mat &image_layer, cv::Mat &preview_layer, const cv::Vec3b &color,
    const std::vector<cv::Point> &perspectivePoints):
  LineTool(image_layer, preview_layer, color),
  perspectivePoints_(perspectivePoints)
{

}

void PerspectiveLineTool::mouse_press(const cv::Point &position)
{
  LineTool::mouse_press(position);

  //Enable directions up, down, left, right by adding fake perspective points
  dPerspectivePoints.clear();
  dPerspectivePoints.push_back(cv::Point(lastClickPoint_.x + 10, lastClickPoint_.y));
  dPerspectivePoints.push_back(cv::Point(lastClickPoint_.x - 10, lastClickPoint_.y));
  dPerspectivePoints.push_back(cv::Point(lastClickPoint_.x, lastClickPoint_.y + 10));
  dPerspectivePoints.push_back(cv::Point(lastClickPoint_.x, lastClickPoint_.y - 10));
  dPerspectivePoints.insert(dPerspectivePoints.end(), perspectivePoints_.begin(), perspectivePoints_.end());

}

void PerspectiveLineTool::mouse_move(const cv::Point &position)
{
  if(mouse_clicked_)
  {

    //Reverse y-coordinates
    cv::Point rPosition = cv::Point(position.x, -position.y);
    std::cout << "rPosition = " << rPosition << std::endl;

    cv::Point rLastClickPoint = cv::Point(lastClickPoint_.x, -lastClickPoint_.y);
    std::cout << "rLastClickPoint = " << rLastClickPoint << std::endl;

    //Calculate vector from click point to mouse position point
    cv::Point rUserVec = rPosition - rLastClickPoint;
    //Calculate opposite  direction vector
    cv::Point rOppositeUserVec = -1 * rUserVec;

    //Search for nearest perspective point
    double minAngle = 3.15;
    cv::Point rNearestPerspectivePoint;
    cv::Point rNearestPerspectiveVec;
    bool rNearestIsOpposite = false;

    for(size_t i = 0; i < dPerspectivePoints.size(); i++)
    {
      //Reverse y-coordinate
      cv::Point rPerspectivePoint = cv::Point(dPerspectivePoints[i].x, -dPerspectivePoints[i].y);

      //Calculate vector from click point to perspective point
      cv::Point rPerspectiveVec = rPerspectivePoint - rLastClickPoint;

      //Calculate angle between the user vector and perspective vector
      double angle1 = std::abs(std::acos(rUserVec.ddot(rPerspectiveVec)
                                         / (cv::norm(rUserVec) * cv::norm(rPerspectiveVec))));

      //Calculate angle between opposite user vector and perspective vector
      double angle2 = std::abs(std::acos(rOppositeUserVec.ddot(rPerspectiveVec)
                                         / (cv::norm(rOppositeUserVec) * cv::norm(rPerspectiveVec))));

      std::cout << "Perspective point [ " << i << " ]" << std::endl;
      std::cout << "user vector = ( " << rUserVec.x << ", " << rUserVec.y << ")" << std::endl;
      std::cout << "perspective vector = ( " << rPerspectiveVec.x << ", " << rPerspectiveVec.y << ")" << std::endl;
      std::cout << "norms = " << cv::norm(rUserVec) << ", " << cv::norm(rPerspectiveVec) << std::endl;
      std::cout << "angles = " << angle1 << ", " << angle2 << std::endl << std::endl;

      bool opposite = false;
      double angle = angle1;
      if(angle2 < angle)
      {
        angle = angle2;
        opposite = true;
      }

      if(angle < minAngle)
      {
        minAngle = angle;
        rNearestPerspectivePoint = rPerspectivePoint;
        rNearestPerspectiveVec = rPerspectiveVec;
        rNearestIsOpposite = opposite;
      }
    }

    //Normalize perspective vector
    cv::Point2d rNormPerspectiveVec = cv::Point2d(rNearestPerspectiveVec) / cv::norm(rNearestPerspectiveVec);
    std::cout << "normalized perspective vector = " << rNormPerspectiveVec << std::endl;

    if(rNearestIsOpposite)
      rNormPerspectiveVec *= -1;


    //Calculate length of user vector
    double length = cv::norm(rUserVec);

    //Calculate final line vector
    cv::Point rFinalVec = rLastClickPoint + cv::Point2i(length * rNormPerspectiveVec);

    //Draw line
    LineTool::mouse_move(cv::Point(rFinalVec.x, -rFinalVec.y));

  }
}
