#ifndef IOBMP_HPP
#define IOBMP_HPP
#include <fstream>
#include "bmpDef24.hpp"

namespace bmp
{
  BMPUnified24 readBmp24(std::ifstream & fin);
  void writeBmp24(std::ofstream & in, const BMPUnified24 & bmpFile);
}

#endif
