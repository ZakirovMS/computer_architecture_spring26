#ifndef BMPDEF8_HPP
#define BMPDEF8_HPP
#include <cstdint>
#include <vector>
#include "bmpDef.hpp"

#pragma pack(push, 1) // Unambiguous fixation of data alignment in structures

namespace bmp
{
  // Define a pixel structure
  struct RGBPixel8
  {
    uint8_t blue;           //Blue in 24
    uint8_t green;          //Green in 24
    uint8_t red;            //Red in 24
  };

  // BITMAPFILEHEADER:
  struct BMPUnified8 final: public BMPUnified
  {
    std::vector< int32_t > palette[256];
    std::vector< int8_t > pixels;
  };
}

#pragma pack(pop)

#endif
