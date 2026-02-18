#include "bmpProcessing.hpp"
#include <stdexcept>
#include <limits>
#include "bmpDef24.hpp"

bmp::BMPUnified24 bmp::binarizeBmp(const BMPUnified24 & bmpFile, float thresholdCoeff)
{
  if (thresholdCoeff > 1 || thresholdCoeff < 0)
  {
    throw std::logic_error("Invalid binarization parameter");
  }

  BMPUnified24 resBmp = bmpFile;
  int threshold = std::numeric_limits< uint8_t >::max() * thresholdCoeff;

  for (size_t i = 0; i < resBmp.pixels.size(); ++i)
  {
    float binarizaton = bmpFile.pixels[i].blue + bmpFile.pixels[i].red + bmpFile.pixels[i].green / 3;
    if (threshold < binarizaton)
    {
      resBmp.pixels[i].blue = std::numeric_limits< uint8_t >::max();
      resBmp.pixels[i].red = std::numeric_limits< uint8_t >::max();
      resBmp.pixels[i].green = std::numeric_limits< uint8_t >::max();
    }
    else
    {
      resBmp.pixels[i].blue = std::numeric_limits< uint8_t >::min();
      resBmp.pixels[i].red = std::numeric_limits< uint8_t >::min();
      resBmp.pixels[i].green = std::numeric_limits< uint8_t >::min();  
    }
  }

  return resBmp;
}

void analyzeBmp(std::ofstream & in, const bmp::BMPUnified24 & bmpFile)
{
  
}

/*
bmp::BMPUnified bmp::convertBmp(const BMPUnified & bmpFile)
{}
*/
