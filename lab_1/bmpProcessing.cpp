#include "bmpProcessing.hpp"
#include <stdexcept>
#include <limits>
#include <iostream>
#include "bmpDef24.hpp"

void bmp::binarizeBmp24(BMPUnified24 & bmpFile, float thresholdCoeff)
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

  bmpFile = resBmp;
}

void bmp::binarizeBmp8(BMPUnified8 & bmpFile, float thresholdCoeff)
{
  if (thresholdCoeff > 1 || thresholdCoeff < 0)
  {
    throw std::logic_error("Invalid binarization parameter");
  }

  BMPUnified8 resBmp = bmpFile;
  uint8_t threshold = static_cast< uint8_t >(255 * thresholdCoeff);
  resBmp.palette[0] = 0x00FFFFFF;
  resBmp.palette[1] = 0x00000000;
  
  for (size_t i = 0; i < bmpFile.pixels.size(); ++i)
  {
    uint8_t index = bmpFile.pixels[i];
    uint32_t color = bmpFile.palette[index];

    uint8_t brightness = static_cast<uint8_t>((((color >> 0) & 0xFF) + ((color >> 8) & 0xFF) + ((color >> 16) & 0xFF)) / 3);

    resBmp.pixels[i] = (brightness > threshold) ? 0 : 1;
  }

  bmpFile = resBmp;
}

void bmp::binarizeBmp(BMPUnified * bmpFile, float thresholdCoeff)
{
  if (bmpFile->infoHeader.biBitCount == 24)
  {
    binarizeBmp24(*static_cast< BMPUnified24 * >(bmpFile), thresholdCoeff);
  }
  else if (bmpFile->infoHeader.biBitCount == 8)
  {
    binarizeBmp8(*static_cast< BMPUnified8 * >(bmpFile), thresholdCoeff);
  }
}

void bmp::analyzeBmp(std::ostream & out, const BMPUnified * bmpFile)
{
  std::cout << "Bit per pixel: " << bmpFile->infoHeader.biBitCount << '\n';
  std::cout << "Height: " << bmpFile->infoHeader.biHeight << '\n';
  std::cout << "Width: " << bmpFile->infoHeader.biWidth << '\n';
}

/*
bmp::BMPUnified bmp::convertBmp(const BMPUnified & bmpFile)
{}
*/
