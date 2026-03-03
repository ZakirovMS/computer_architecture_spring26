#include "IOBmp.hpp"
#include <stdexcept>
#include <vector>
#include "bmpDef24.hpp"
#include "bmpDef8.hpp"

namespace
{
  void readData24(std::ifstream & fin, bmp::BMPUnified24 * bmpFile)
  {
    std::vector< bmp::RGBPixel24 > pixelsBmp(bmpFile->infoHeader.biWidth * bmpFile->infoHeader.biHeight);
    for (int y = bmpFile->infoHeader.biHeight - 1; y >= 0; --y)
    {
      for (int x = 0; x < bmpFile->infoHeader.biWidth; ++x)
      {
        fin.read(reinterpret_cast< char * >(&pixelsBmp[y * bmpFile->infoHeader.biWidth + x]), sizeof(bmp::RGBPixel24));
      }
    }

    bmpFile->pixels = pixelsBmp;
  }

  void readData8(std::ifstream & fin, bmp::BMPUnified8 * bmpFile)
  {
    for (size_t i = 0; i < bmpFile->palette.size(); ++i)
    {
      fin.read(reinterpret_cast< char * >(&bmpFile->palette[i]), sizeof(int32_t));
    }
    std::vector< uint8_t > pixelsBmp(bmpFile->infoHeader.biWidth * bmpFile->infoHeader.biHeight);
    for (int y = bmpFile->infoHeader.biHeight - 1; y >= 0; --y)
    {
      for (int x = 0; x < bmpFile->infoHeader.biWidth; ++x)
      {
        fin.read(reinterpret_cast< char * >(&pixelsBmp[y * bmpFile->infoHeader.biWidth + x]), sizeof(uint8_t));
      }
    }

    bmpFile->pixels = pixelsBmp;
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
  else if (iHead.biBitCount == 8)
  {
    BMPUnified8 * stubBmp = new BMPUnified8;
    stubBmp->fileHeader = fHead;
    stubBmp->infoHeader = iHead;
    readData8(fin, stubBmp);
    resBmp = stubBmp;
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

void bmp::writeBmp8(std::ofstream & fout, const BMPUnified8 & bmpFile)
{
    fout.write(reinterpret_cast< const char * >(&bmpFile.fileHeader), sizeof(BMPFileHeader));
    fout.write(reinterpret_cast< const char * >(&bmpFile.infoHeader), sizeof(BMPInfoHeader));
    for (int i = 0; i < bmpFile.palette.size(); ++i)
    {
      const int32_t & paletteEl = bmpFile.palette[i];
      fout.write(reinterpret_cast< const char * >(&paletteEl), sizeof(int32_t));
    }

    fout.seekp(bmpFile.fileHeader.bfOffBits, std::ios::beg);
    
    int width = bmpFile.infoHeader.biWidth;
    int height = bmpFile.infoHeader.biHeight;
    for (int y = height - 1; y >= 0; --y)
    {
        for (int x = 0; x < width; ++x)
        {
            const int8_t & pixel = bmpFile.pixels[y * width + x];
            fout.write(reinterpret_cast< const char * >(&pixel), sizeof(int8_t));
        }
    }
}

void bmp::writeBmp(std::ofstream & fout, const BMPUnified * bmpFile)
{
  if (bmpFile->infoHeader.biBitCount == 24)
  {
    writeBmp24(fout, *static_cast< const BMPUnified24 * >(bmpFile));
  }
  else if (bmpFile->infoHeader.biBitCount == 8)
  {
    writeBmp8(fout, *static_cast< const BMPUnified8 * >(bmpFile));
  }
}
