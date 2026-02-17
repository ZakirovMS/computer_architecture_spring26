#ifndef IOBMP_HPP
#define IOBMP_HPP
#include <fstream>
#include "bmpDef.hpp"

namespace bmp
{
  BMPUnified readBmp(std::ifstream & fin);
  void writeBmp(std::ofstream & in, const BMPUnified & bmpFile);
}

#endif
