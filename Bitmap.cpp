#include <fstream>
#include "./Bitmap.h"
#include "./BitmapInfoHeader.h"
#include "./BitmapFileHeader.h"

Bitmap::Bitmap(int width, int height): m_width(width), m_height(height), 
    m_pPixels(new uint8_t [width * height * 3]{})
{

}

bool Bitmap::write(std::string filename)
{
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;

    fileHeader.fileSize = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) 
        + m_width * m_height * 3;
    // dataOffset tessl you how far into the file the data begins
    fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    infoHeader.width = m_width;
    infoHeader.height = m_height;

    std::ofstream file;

    file.open(filename, std::ios::out|std::ios::binary);

    if (!file)
    {
        return false;
    }

    file.write((char *)&fileHeader, sizeof(fileHeader));
    file.write((char *)&infoHeader, sizeof(infoHeader));
    file.write((char *)m_pPixels.get(), m_width * m_height * 3);

    file.close();

    if (!file)
    {
        return false;
    }

    return true;
}

// x and y are x and y coordinates of the pixel
void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
    uint8_t *pPixel = m_pPixels.get();

    // set pPixel to number of bytes in all the rows we're interested in
    // because each pixel takes up 3 bytes, multiply by 3
    // add in the location on the row via + (x * 3)
    // ends up pointing pPixel to the location in the bitmap you want to set
    // the pixel value
    pPixel += (y * 3) * m_width + (x * 3);

    // In little endian format you store the least significant byte in the area
    // of memory with smallest memory address. so 876543, 43 is the least significant
    // number and would be stored first in little endian format because 
    // 000000 - the first pair of 00's represent the smallest memory address
    // and thus contain the least significant number.
    pPixel[0] = blue;
    pPixel[1] = green;
    pPixel[2] = red;
}

Bitmap::~Bitmap()
{

}