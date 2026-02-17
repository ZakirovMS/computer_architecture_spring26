#include "IOBmp.hpp"
#include <stdexcept>
#include <vector>
#include "bmpDef24.hpp"

#include <iostream>

bmp::BMPUnified24 bmp::readBmp24(std::ifstream & fin)
{
  BMPUnified24 resBmp;
  fin.read(reinterpret_cast< char * >(&resBmp.fileHeader), sizeof(BMPFileHeader24));
  if (resBmp.fileHeader.header[0] != 'B' || resBmp.fileHeader.header[1] != 'M')
  {
    std::cout << resBmp.fileHeader.header[0] << ' ' << resBmp.fileHeader.header[1] << std::endl;
    throw std::invalid_argument("Incorrect format");
  }

  fin.read(reinterpret_cast< char * >(&resBmp.infoHeader), sizeof(resBmp.infoHeader));

  fin.seekg(resBmp.fileHeader.bfOffBits, std::ios::beg);

  std::vector< RGBPixel24 > pixels(resBmp.infoHeader.biWidth * resBmp.infoHeader.biHeight);
  for (int y = resBmp.infoHeader.biHeight - 1; y >= 0; --y)
  {
    for (int x = 0; x < resBmp.infoHeader.biWidth; ++x)
    {
      fin.read(reinterpret_cast< char * >(&pixels[y * resBmp.infoHeader.biWidth + x]), sizeof(RGBPixel24));
    }
  }

  resBmp.pixels = pixels;
  return resBmp;
}

void bmp::writeBmp24(std::ofstream & fout, const BMPUnified24 & bmpFile)
{
    fout.write(reinterpret_cast< const char * >(&bmpFile.fileHeader), sizeof(BMPFileHeader24));
    fout.write(reinterpret_cast< const char * >(&bmpFile.infoHeader), sizeof(BMPInfoHeader24));
    fout.seekp(bmpFile.fileHeader.bfOffBits, std::ios::beg);
    
    int width = bmpFile.infoHeader.biWidth;
    int height = bmpFile.infoHeader.biHeight;

    for (int y = height - 1; y >= 0; --y)
    {
        for (int x = 0; x < width; ++x)
        {
            const RGBPixel24 & pixel = bmpFile.pixels[y * width + x];
            fout.write(reinterpret_cast< const char * >(&pixel), sizeof(RGBPixel24));
        }
    }
}
