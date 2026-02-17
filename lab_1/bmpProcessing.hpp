#ifndef BMPPROCESSING_HPP
#define BMPPROCESSING_HPP
#include "bmpDef.hpp"
#include <string>

namespace bmp
{
  BMPUnified binarizeBmp(const BMPUnified & bmpFile, float threshold);
  BMPUnified convertBmp(const BMPUnified & bmpFile);  // from 8 bit-pixel to 16 bit-pixel
}

#endif
