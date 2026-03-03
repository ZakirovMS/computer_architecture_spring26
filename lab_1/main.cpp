#include <fstream>
#include <iostream>
#include "bmpDef24.hpp"
#include "bmpDef8.hpp"
#include "bmpProcessing.hpp"
#include "IOBmp.hpp"

int main()
{
  std::ifstream file("../src/test8.bmp", std::ios::binary);
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

  std::ofstream fout("../src/result8.bmp", std::ios::binary);
  if (!fout.is_open())
  {
    std::cerr << "Incorrect result file opening" << '\n';
    return 1;
  }

  try
  {
    bmp::binarizeBmp(bmp_i, 0.15);
  }
  catch (const std::logic_error & e)
  {
    std::cerr << e.what() << '\n';
  }

  bmp::writeBmp(fout, bmp_i);
  delete bmp_i;
}
