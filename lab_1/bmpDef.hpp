#include <cstdint>

#pragma pack(push, 1) // Ensure that structure members are not padded

// BITMAPFILEHEADER:
struct BMPFHeader
{
  char header[2];       // File type - 'BM' for Bitmap
  uint32_t fileSize;    // File size in bytes
  uint32_t bfReserved1; // Reserved (usually 0)
  uint32_t bfReserved2; // Reserved too (usually 0)
  uint32_t bfOffBits;   // Offset to the pixel data
};

struct DIBHeader
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

// Define a pixel structure for RGB
struct RGBPixel
{
  uint8_t blue;
  uint8_t green;
  uint8_t red;
};

#pragma pack(pop)