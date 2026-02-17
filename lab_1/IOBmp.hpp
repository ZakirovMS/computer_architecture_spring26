#ifndef IOBMP_HPP
#define IOBMP_HPP
#include <iostream>
#include "bmpDef.hpp"

namespace bmp
{
  BMPUnified readBmp(std::istream & in, const std::string & fileName);
  void writeBmp(std::ostream & in, const std::string & fileName);
}

#endif
