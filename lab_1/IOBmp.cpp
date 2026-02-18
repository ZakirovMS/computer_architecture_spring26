#include "IOBmp.hpp"
#include <stdexcept>
#include <vector>
#include "bmpDef24.hpp"

namespace
{
  void readData24(std::ifstream & fin, bmp::BMPUnified24 * bmpFile)
  {
    std::vector< bmp::RGBPixel24 > pixels(bmpFile->infoHeader.biWidth * bmpFile->infoHeader.biHeight);
    for (int y = bmpFile->infoHeader.biHeight - 1; y >= 0; --y)
    {
      for (int x = 0; x < bmpFile->infoHeader.biWidth; ++x)
      {
        fin.read(reinterpret_cast< char * >(&pixels[y * bmpFile->infoHeader.biWidth + x]), sizeof(bmp::RGBPixel24));
      }
    }

    bmpFile->pixels = pixels;
  }
}

bmp::BMPUnified * bmp::readBmp(std::ifstream & fin)
{
  bmp::BMPFileHeader fHead;
  bmp::BMPInfoHeader iHead;
  fin.read(reinterpret_cast< char * >(&fHead), sizeof(BMPFileHeader));
  if (fHead.header[0] != 'B' || fHead.header[1] != 'M')
  {
    throw std::invalid_argument("Incorrect format");
  }

  fin.read(reinterpret_cast< char * >(&iHead), sizeof(BMPInfoHeader));

  BMPUnified * resBmp = nullptr;
  if (iHead.biBitCount == 24)
  {
    BMPUnified24 * stubBmp = new BMPUnified24;
    stubBmp->fileHeader = fHead;
    stubBmp->infoHeader = iHead;
    readData24(fin, stubBmp);
    resBmp = stubBmp;
  }
  else if (iHead.biBitCount == 16)
  {

  }

  return resBmp;
}

void bmp::writeBmp24(std::ofstream & fout, const BMPUnified24 & bmpFile)
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
            const RGBPixel24 & pixel = bmpFile.pixels[y * width + x];
            fout.write(reinterpret_cast< const char * >(&pixel), sizeof(RGBPixel24));
        }
    }
}
