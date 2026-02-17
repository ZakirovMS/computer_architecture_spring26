#include "bmpProcessing.hpp"
#include <stdexcept>
#include <limits>
#include "bmpDef.hpp"

bmp::BMPUnified bmp::binarizeBmp(const BMPUnified & bmpFile, float thresholdCoeff)
{
  if (thresholdCoeff > 1 || thresholdCoeff < 0)
  {
    throw std::logic_error("Invalid binarization parameter");
  }

  BMPUnified resBmp = bmpFile;
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

/*
bmp::BMPUnified bmp::convertBmp(const BMPUnified & bmpFile)
{}
*/
