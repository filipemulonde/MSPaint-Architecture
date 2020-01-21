#ifndef IMAGEDRAWER_H
#define IMAGEDRAWER_H

#include <string>
#include <vector>
#include <map>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "PencilTool.h"
#include "LineTool.h"
#include "PerspectiveLineTool.h"
#include "AxonometryLineTool.h"
#include "RulerTool.h"

class ImageDrawer
{

public:

  ImageDrawer(int imageWidth, int imageHeight);
  ImageDrawer(const std::string& image_filepath);
  virtual ~ImageDrawer();

//  TODO:
//  void resize(int width, int height);
//  void save(const std::string& out_filepath);
//  void open(const std::string& in_filepath);

  void mouse_move(int x, int y);
  void mouse_press(int x, int y);
  void mouse_release(int x, int y);

  cv::Mat getFrame();
  int getHeight() const;
  int getWidth() const;

  enum tool_t{
    PENCIL,
    LINE,
    ERASER,
    RULER,
    ANGLE_MEASURE};

  enum work_mode_t{
    NORMAL,
    PERSPECTIVE,
    AXONOMETRY};

  enum anchoring_options_t{
    ANCHOR_TO_GRID,
    ANCHOR_LINE_ENDS,
    ANCHOR_VERTICAL_LINE_ENDS,
    ANCHOR_HORIZONTAL_LINE_ENDS};

//  TODO:
  void setActiveColor(int r, int g, int b);

  void setActiveTool(const tool_t& tool);
  void setActiveMode(const work_mode_t& mode);
//  void setAnchoringOptions(const anchoring_options_t& anchoring_option, bool active);
  void setAxonometryAngles(double alpha, double beta);
  void setGridLines(int hor_tick_px, int ver_tick_px);
  void setGridLinesVisible(bool visible);
//  void setPixelsPerMeter(float PPM);

  void resetPerspectivePoints();
  void addPerspectivePoints();
  bool applyPerspectivePoints();
//  void setPerspectivePointsVisible(bool visible);

private:

  Tool *activeTool;
  tool_t activeToolType;
  work_mode_t activeMode;
  cv::Vec3b activeColor;

  cv::Mat image_layer;
  cv::Mat preview_layer;
  cv::Mat perspective_points_layer;
//  cv::Mat grid_layer;

  PencilTool *pencilTool;
  LineTool *lineTool;
  RulerTool *rulerTool;

  PerspectiveLineTool *perspectiveLineTool;
  std::vector<cv::Point> perspectivePoints;
  cv::Vec3b perspectivePointColor = cv::Vec3b(0, 0, 255);
  bool isAddingPerspectivePoints = false;

  AxonometryLineTool *axonometryLineTool;
  std::vector<double> axonometryAngles;
//  std::vector<cv::Point> anchorPoints;
//  std::map<anchoring_options_t, bool> anchoringOptions;
//  float ppm;
//  bool ppm_is_set = false;

  int horTickPx, verTickPx;
  bool gridlinesEnabled;

  void addPerspectivePoint(int x, int y);

};

#endif // IMAGEDRAWER_H
