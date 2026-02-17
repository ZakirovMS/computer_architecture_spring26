#include "IOBmp.hpp"
#include <exception>
#include <vector>
#include "bmpDef.hpp"

#include <iostream>

bmp::BMPUnified bmp::readBmp(std::ifstream & fin)
{
  BMPUnified resBmp;
  fin.read(reinterpret_cast< char * >(&resBmp.fileHeader), sizeof(BMPFileHeader));
  if (resBmp.fileHeader.header[0] != 'B' || resBmp.fileHeader.header[1] != 'M')
  {
    std::cout << resBmp.fileHeader.header[0] << ' ' << resBmp.fileHeader.header[1] << std::endl;
    throw std::invalid_argument("Incorrect format");
  }

  fin.read(reinterpret_cast< char * >(&resBmp.infoHeader), sizeof(resBmp.infoHeader));

  fin.seekg(resBmp.fileHeader.bfOffBits, std::ios::beg);

  std::vector< RGBPixel > pixels(resBmp.infoHeader.biWidth * resBmp.infoHeader.biHeight);
  for (int y = resBmp.infoHeader.biHeight - 1; y >= 0; --y)
  {
    for (int x = 0; x < resBmp.infoHeader.biWidth; ++x)
    {
      fin.read(reinterpret_cast< char * >(&pixels[y * resBmp.infoHeader.biWidth + x]), sizeof(RGBPixel));
    }
  }

  resBmp.pixels = pixels;
  return resBmp;
}
/*
void bmp::writeBmp(std::ofstream & in, const BMPUnified & bmpFile)
{}
*/
