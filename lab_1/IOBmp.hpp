#ifndef IOBMP_HPP
#define IOBMP_HPP
#include <fstream>
#include "bmpDef24.hpp"
#include "bmpDef8.hpp"

namespace bmp
{
  BMPUnified * readBmp(std::ifstream & fin);
  void writeBmp24(std::ofstream & in, const BMPUnified24 & bmpFile);
  void writeBmp8(std::ofstream & fout, const BMPUnified8 & bmpFile);
  void writeBmp(std::ofstream & fout, const BMPUnified * bmpFile);
}

#endif
