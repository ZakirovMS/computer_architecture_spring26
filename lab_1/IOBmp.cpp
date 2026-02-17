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

void bmp::writeBmp(std::ofstream & fout, const BMPUnified & bmpFile)
{
    fout.write(reinterpret_cast< const char * >(&bmpFile.fileHeader), sizeof(BMPFileHeader));
    fout.write(reinterpret_cast< const char * >(&bmpFile.infoHeader), sizeof(BMPInfoHeader));
    fout.seekp(bmpFile.fileHeader.bfOffBits, std::ios::beg);
    
    int width = bmpFile.infoHeader.biWidth;
    int height = bmpFile.infoHeader.biHeight;

    for (int y = height - 1; y >= 0; --y)
    {
        for (int x = 0; x < width; ++x)
        {
            const RGBPixel & pixel = bmpFile.pixels[y * width + x];
            fout.write(reinterpret_cast< const char * >(&pixel), sizeof(RGBPixel));
        }
    }
}
