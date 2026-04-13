#include <fstream>
#include <iostream>
#include "bmpDef24.hpp"
#include "bmpDef8.hpp"
#include "bmpProcessing.hpp"
#include "IOBmp.hpp"

int main()
{
  std::ifstream file("../src/someBmp.bmp", std::ios::binary);
  if (!file.is_open())
  {
    std::cerr << "Incorrect file opening" << '\n';
    return 1;
  }

  bmp::BMPUnified * bmp_i;

  try
  {
    bmp_i = bmp::readBmp(file);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  bmp::analyzeBmp(std::cout, bmp_i);
  std::ofstream fout("../src/result24.bmp", std::ios::binary);
  if (!fout.is_open())
  {
    std::cerr << "Incorrect result file opening" << '\n';
    return 1;
  }

/*
  try
  {
    bmp::binarizeBmp(bmp_i, 0.98);
  }
  catch (const std::logic_error & e)
  {
    std::cerr << e.what() << '\n';
  }

  bmp::writeBmp(fout, bmp_i);
*/

bmp::writeBmp(fout, bmp::convertBmp(static_cast< bmp::BMPUnified24 * >(bmp_i)));
}
