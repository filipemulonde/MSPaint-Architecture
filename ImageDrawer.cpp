#include "ImageDrawer.h"


ImageDrawer::ImageDrawer(int imageWidth, int imageHeight)
{
  image_layer = cv::Mat(imageHeight, imageWidth, CV_8UC3, cv::Scalar(255, 255, 255));
  image_layer.copyTo(preview_layer);

  pencilTool = new PencilTool(image_layer, preview_layer, activeColor);

  activeTool = pencilTool;
  activeToolType = tool_t::PENCIL;
  activeColor = cv::Vec3b(0,0,0);
  activeMode = work_mode_t::NORMAL;

}
ImageDrawer::ImageDrawer(const std::string& image_filepath)
{
  image_layer = cv::imread(image_filepath);
}
cv::Mat ImageDrawer::getFrame() const
{
  return preview_layer;
}
void ImageDrawer::mouse_move(int x, int y)
{
  activeTool->mouse_move(cv::Point(x, y));
}
void ImageDrawer::mouse_press(int x, int y)
{
  activeTool->mouse_press(cv::Point(x, y));
}
void ImageDrawer::mouse_release(int x, int y)
{
  activeTool->mouse_release(cv::Point(x, y));
}
ImageDrawer::~ImageDrawer()
{
  delete pencilTool;
}
