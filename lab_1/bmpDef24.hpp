#ifndef BMPDEF_HPP
#define BMPDEF_HPP
#include <cstdint>
#include <vector>

#pragma pack(push, 1) // Unambiguous fixation of data alignment in structures
namespace bmp
{

  // BITMAPFILEEADER:
  struct BMPFileHeader
  {
    char header[2];       // File type - 'BM' for Bitmap
    uint32_t fileSize;    // File size in bytes
    uint16_t bfReserved1; // Reserved (usually 0)
    uint16_t bfReserved2; // Reserved too (usually 0)
    uint32_t bfOffBits;   // Offset to the pixel data
  };

  // BITMAPINFOEADER
  struct BMPInfoHeader
  {
    uint32_t biSize;         // BMPFHeader size (40 bytes)
    int32_t biWidth;         // Image width
    int32_t biHeight;        // Image height
    uint16_t biPlanes;       // Color planes (usually 1)
    uint16_t biBitCount;     // ! Bits per pixel (24 for RGB)
    uint32_t biCompression;  // Compression type (0 for none)
    uint32_t biSizeImage;    // Image size (may be 0 for uncompressed)
    int32_t biXPelsPerMeter; // Horizontal resolution (pixels per meter)
    int32_t biYPelsPerMeter; // Vertical resolution (pixels per meter)
    uint32_t biClrUsed;      // Number of colors
    uint32_t biClrImportant; // Important colors
  };

  // Define a pixel structure
  struct RGBPixel24
  {
    uint8_t blue;           //Blue in 24
    uint8_t green;          //Green in 24
    uint8_t red;            //Red in 24
  };

  struct RGBPixel16
  {
    uint16_t bitSetBGR;     //bbbbbgggggrrrrr0
  };

  struct BMPUnified
  {
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
  };

  // BITMAPFILEHEADER:
  struct BMPUnified24 final: public BMPUnified
  {
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    std::vector< RGBPixel24 > pixels;
  };

  struct BMPUnified16 final: public BMPUnified
  {
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;
    std::vector< RGBPixel16 > pixels;
  };
}
#pragma pack(pop)

#endif
