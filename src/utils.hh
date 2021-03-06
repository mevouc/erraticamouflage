#pragma once

# include <cstdint>
# include <opencv2/core.hpp>

namespace erraticamo
{
  namespace utils
  {
    double scale(double val, double src_min = -1.0, double src_max = 1.,
                 double dst_min = 0., double dst_max = 1.);

    std::uint8_t binarize_color(std::uint8_t val, std::uint8_t treshold = 128);

    cv::Vec3b complementary_color(cv::Vec3b color);

    template<typename Int>
    Int uniform_random(Int max);
  }
}

# include "utils.hxx"
