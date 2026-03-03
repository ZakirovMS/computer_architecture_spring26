#ifndef BMPDEF8_HPP
#define BMPDEF8_HPP
#include <cstdint>
#include <vector>
#include "bmpDef.hpp"

#pragma pack(push, 1) // Unambiguous fixation of data alignment in structures

namespace bmp
{

  // BITMAPFILEHEADER:
  struct BMPUnified8 final: public BMPUnified
  {
    std::vector< uint32_t > palette = std::vector< uint32_t >(256);
    std::vector< uint8_t > pixels;
  };
}

#pragma pack(pop)

#endif
