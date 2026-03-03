#include "bmpProcessing.hpp"
#include <stdexcept>
#include <limits>
#include <iostream>
#include <vector>
#include "bmpDef24.hpp"

namespace
{
  void setGreenPalette(bmp::BMPUnified8 & bmpFile)
  {
    for (size_t i = 0; i < 256; ++i)
    {
      uint8_t green = static_cast< uint8_t >(i);
      bmpFile.palette[i] = (static_cast< uint32_t >(green) << 8);
    }
  }

  void setPinkPalette(bmp::BMPUnified8 & bmpFile)
  {
    constexpr uint8_t targetBlue  = 180;
    constexpr uint8_t targetGreen = 105;
    constexpr uint8_t targetRed   = 255;

    for (size_t i = 0; i < 256; ++i)
    {
      uint8_t b = static_cast<uint8_t>((i * targetBlue)  / 255);
      uint8_t g = static_cast<uint8_t>((i * targetGreen) / 255);
      uint8_t r = static_cast<uint8_t>((i * targetRed)   / 255);

      bmpFile.palette[i] = (static_cast<uint32_t>(b) << 0) | (static_cast<uint32_t>(g) << 8) | (static_cast<uint32_t>(r) << 16);
    }
  }
}

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


bmp::BMPUnified8 * bmp::convertBmp(BMPUnified24 * bmpFile)
{
  BMPUnified8 * result = new BMPUnified8;
  result->fileHeader = bmpFile->fileHeader;
  result->infoHeader = bmpFile->infoHeader;
  result->infoHeader.biBitCount = 8;
  result->infoHeader.biSizeImage = result->infoHeader.biHeight * result->infoHeader.biWidth;
  result->fileHeader.bfOffBits = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + 256 * 4;
  result->fileHeader.fileSize = result->fileHeader.bfOffBits + result->infoHeader.biSizeImage;
  setGreenPalette(*result);
  result->pixels = std::vector< uint8_t >(result->infoHeader.biHeight * result->infoHeader.biWidth);
  for (size_t i = 0; i < bmpFile->pixels.size(); ++i)
  {
    result->pixels[i] = static_cast< uint8_t >((bmpFile->pixels[i].red + bmpFile->pixels[i].green + bmpFile->pixels[i].blue) / 3);
  }

  return result;
}
