#include <fstream>
#include <iostream>
#include "bmpDef24.hpp"
#include "bmpProcessing.hpp"
#include "IOBmp.hpp"

int main()
{
  std::ifstream file("../src/test24.bmp", std::ios::binary);
  if (!file.is_open())
  {
    std::cerr << "Incorrect file opening" << '\n';
    return 1;
  }

  bmp::BMPUnified24 bmp_i;
  try
  {
    bmp_i = bmp::readBmp24(file);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }

  std::ofstream fout("../src/result24.bmp", std::ios::binary);
  if (!fout.is_open())
  {
    std::cerr << "Incorrect result file opening" << '\n';
    return 1;
  }

  bmp::writeBmp24(fout, bmp::binarizeBmp(bmp_i, 0.98));
}
