#ifndef BMPPROCESSING_HPP
#define BMPPROCESSING_HPP
#include "bmpDef24.hpp"
#include "bmpDef8.hpp"
#include <string>

namespace bmp
{
  void binarizeBmp24(BMPUnified24 & bmpFile, float thresholdCoeff);
  void binarizeBmp8(BMPUnified8 & bmpFile, float thresholdCoeff);
  void binarizeBmp(BMPUnified * bmpFile, float thresholdCoeff);
  void analyzeBmp(std::ostream & out, const BMPUnified * bmpFile);
  void convertBmp(const BMPUnified * bmpFile);
}

#endif
