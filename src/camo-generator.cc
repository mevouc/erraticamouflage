#include <cassert>

#include "camo-generator.hh"
#include "utils.hh"

erraticamo::CamoGenerator::CamoGenerator(size_t nb_layers, size_t width,
                                         size_t height, cv::Vec3b color)
  : nb_layers_(nb_layers)
  , img_(width, height, CV_8UC3, utils::complementary_color(color))
  , colors_(nb_layers + 1)
{
  generate_colors_(color);
}

const cv::Mat&
erraticamo::CamoGenerator::operator()()
{
  generate_();
  return img_;
}

void
erraticamo::CamoGenerator::generate_()
{
  if (nb_layers_ == 0)
    return;

  const auto bottom_layer = Layer(img_.cols, img_.rows);
  add_layer_(bottom_layer);

  for (auto i = 1u; i < nb_layers_; ++i)
    add_layer_(Layer(img_.cols, img_.rows), i); // TODO: change treshold
}

void
erraticamo::CamoGenerator::add_layer_(const Layer layer, size_t layer_index)
{
  for (auto j = 0; j < img_.rows; ++j)
    for (auto i = 0; i < img_.cols; ++i)
      if (layer.at(i, j))
      {
        auto& pixel = img_.at<cv::Vec3b>(i, j);
        pixel = colors_.at(layer_index);
      }
}

void
erraticamo::CamoGenerator::generate_colors_(const cv::Vec3b base_color)
{
  //std::uint8_t interval = std::abs(base_color - utils::complementary(colors));
  //std::uint8_t step = 256 / nb_layers_;
  (void)base_color;
  std::uint8_t tmp = 255u;

  for (auto& color : colors_)
  {
    color[0] = color[1] = color[2] = utils::uniform_random<std::uint8_t>(tmp); // TODO: change colors
  }
}
