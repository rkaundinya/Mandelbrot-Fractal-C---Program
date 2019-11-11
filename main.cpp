#include <iostream>
#include <cstdint>
#include <memory>
#include <math.h>
#include "./Mandelbrot.h"
#include "./Bitmap.h"
#include "./ZoomList.h"
#include "./FractalCreator.h"
#include "./RGB.h"

int main()
{
    FractalCreator fractalCreator(800, 600);

    fractalCreator.run("test.bmp");

    std::cout << "Finished" << std::endl;

    return 0;
}