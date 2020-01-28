#include "ImageDrawer.h"
#include <algorithm>
#include <QDebug>

ImageDrawer::ImageDrawer(int imageWidth, int imageHeight)
{
  image_layer = cv::Mat(imageHeight, imageWidth, CV_8UC3, cv::Scalar(255, 255, 255));
  image_layer.copyTo(preview_layer);

  activeColor = cv::Vec3b(0,0,0);
  pencilTool = new PencilTool(image_layer, preview_layer, activeColor);
  lineTool = new LineTool(image_layer, preview_layer, activeColor);
  rulerTool = new RulerTool(image_layer, preview_layer, activeColor);
  perspectiveLineTool = new PerspectiveLineTool(image_layer, preview_layer, activeColor, perspectivePoints);
  axonometryLineTool = new AxonometryLineTool(image_layer, preview_layer, activeColor, axonometryAngles);
  activeTool = pencilTool;
  activeToolType = tool_t::PENCIL;
  activeMode = work_mode_t::NORMAL;
  horTickPx = verTickPx = 10;
  gridlinesEnabled = false;
}

ImageDrawer::ImageDrawer(const std::string& image_filepath)
{
  image_layer = cv::imread(image_filepath);
}

ImageDrawer::~ImageDrawer()
{
  delete pencilTool;
  delete lineTool;
  delete perspectiveLineTool;
}

cv::Mat ImageDrawer::getFrame()
{  
  cv::Mat result;
  preview_layer.copyTo(result);

  if(isAddingPerspectivePoints || activeMode == work_mode_t::PERSPECTIVE)
  {
    std::for_each(perspectivePoints.begin(), perspectivePoints.end(), [&](const cv::Point &p){
      cv::drawMarker(result, p, perspectivePointColor, cv::MARKER_CROSS);
    });
  }

  if(gridlinesEnabled)
  {
    for(int x = 0; x < getWidth(); x += horTickPx)
      cv::line(result, cv::Point(x, 0), cv::Point(x, getHeight()-1), cv::Scalar(160, 160, 160));
    for(int y = 0; y < getHeight(); y += verTickPx)
      cv::line(result, cv::Point(0, y), cv::Point(getWidth()-1, y), cv::Scalar(160, 160, 160));
  }

  return result;
}
void ImageDrawer::resize(int width, int height){


       // image_layer.release();
        image_layer.size[0] = height;
        image_layer.size[1] = width;


};


 cv::Mat ImageDrawer::open(const std::string& in_filepath){


    return image_layer =  cv::imread(in_filepath);


}

int ImageDrawer::getHeight() const
{
  return image_layer.size[0];
}

int ImageDrawer::getWidth() const
{
  return image_layer.size[1];
}

void ImageDrawer::setActiveColor(int r, int g, int b)
{
  activeColor = cv::Vec3b(r, g, b);
  pencilTool->setColor(activeColor);
  lineTool->setColor(activeColor);
  perspectiveLineTool->setColor(activeColor);
  axonometryLineTool->setColor(activeColor);
}

void ImageDrawer::setActiveTool(const ImageDrawer::tool_t &tool)
{
  activeToolType = tool;
  switch(tool)
  {
  case tool_t::PENCIL:
    activeTool = pencilTool;
    break;
  case tool_t::LINE:
    activeTool = lineTool;
    break;
  case tool_t::RULER:
    activeTool = rulerTool;
  default:
    break;
  }
}

void ImageDrawer::setActiveMode(const ImageDrawer::work_mode_t &mode)
{
  activeMode = mode;

  if(activeToolType == tool_t::LINE)
  {
    if(activeMode == work_mode_t::NORMAL)
      activeTool = lineTool;
    else if(activeMode == work_mode_t::PERSPECTIVE)
      activeTool = perspectiveLineTool;
    else if(activeMode == work_mode_t::AXONOMETRY)
      activeTool = axonometryLineTool;
  }
}

void ImageDrawer::setAxonometryAngles(double alpha, double beta)
{
  axonometryAngles.clear();
  axonometryAngles.push_back(alpha);
  axonometryAngles.push_back(beta);
}

void ImageDrawer::setGridLines(int hor_tick_px, int ver_tick_px)
{
  horTickPx = hor_tick_px;
  verTickPx = ver_tick_px;
}

void ImageDrawer::setGridLinesVisible(bool visible)
{
  gridlinesEnabled = visible;
}

void ImageDrawer::resetPerspectivePoints()
{
  perspectivePoints.clear();
  image_layer.copyTo(preview_layer);
}

void ImageDrawer::addPerspectivePoints()
{
  isAddingPerspectivePoints = true;
}

bool ImageDrawer::applyPerspectivePoints()
{
  isAddingPerspectivePoints = false;
  return !perspectivePoints.empty();
}

void ImageDrawer::mouse_move(int x, int y)
{
  qDebug() << "mouse_move";
  activeTool->mouse_move(cv::Point(x, y));
}

void ImageDrawer::mouse_press(int x, int y)
{
  if(isAddingPerspectivePoints)
  {
    perspectivePoints.push_back(cv::Point(x, y));
    return;
  }
  activeTool->mouse_press(cv::Point(x, y));
}

void ImageDrawer::mouse_release(int x, int y)
{
  activeTool->mouse_release(cv::Point(x, y));
}



