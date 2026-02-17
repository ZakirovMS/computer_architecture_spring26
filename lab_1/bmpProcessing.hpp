#ifndef BMPPROCESSING_HPP
#define BMPPROCESSING_HPP
#include "bmpDef24.hpp"
#include <string>

namespace bmp
{
  BMPUnified24 binarizeBmp(const BMPUnified24 & bmpFile, float threshold);
  BMPUnified24 convertBmp(const BMPUnified24 & bmpFile);  // from 8 bit-pixel to 16 bit-pixel
}

#endif
