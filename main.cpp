#include <iostream>
#include <cstdint>
#include <memory>
#include <math.h>
#include "./Mandelbrot.h"
#include "./Bitmap.h"
#include "./ZoomList.h"

int main()
{
    int const WIDTH = 800; 
    int const HEIGHT = 600;

    Bitmap bitmap(WIDTH, HEIGHT);

    double min = 999999;
    double max = -999999;

    ZoomList zoomList(WIDTH, HEIGHT); 

    // Centers zoom on center of screen
    zoomList.add(Zoom(WIDTH/2, HEIGHT/2, 4.0/WIDTH));
    zoomList.add(Zoom(295, HEIGHT - 202, 0.1));
    zoomList.add(Zoom(312, HEIGHT - 304, 0.1));
    //zoomList.add(Zoom(399, HEIGHT - 231, 0.1));
    //zoomList.add(Zoom(59, HEIGHT - 196, 0.1));

    // Histogram of number of iterations. Use this to calculate color
    std::unique_ptr<int[]> histogram(new int[Mandelbrot::MAX_ITERATIONS]{});
    // Store of iterations at a specific coordinate
    std::unique_ptr<int[]> fractal(new int[WIDTH*HEIGHT] { 0 });

    // Create data stores of mandelbrot values here
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            // Implement mandelbrot zoom on each coordinate to render image
            // for all pixels at current zoom level
            std::pair <double, double> coords = zoomList.doZoom(x,y);
            
            int iterations = Mandelbrot::getIterations(coords.first, coords.second);

            fractal[y * WIDTH + x] = iterations; 

            // Adds one to the index of the histogram corresponding to the number of 
            // iterations the current point reaches
            if (iterations != Mandelbrot::MAX_ITERATIONS)
            {
                histogram[iterations]++;
            }
        }
    }

    int total = 0; 
    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i)
    {
        total += histogram[i];
    }

    // Color Pixels on bitmap here
    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;

            // gets you num of iterations per current pixel
            int iterations = fractal[y * WIDTH + x];

            if (iterations != Mandelbrot::MAX_ITERATIONS)
            {
                double hue = 0.0;
                // This loop below increases the color of pixels which have 
                // the number of iterations the nested for loop is currently on.
                // Essentially adds a certian amount of color to each pixel
                // with the particular iteration type. Hue values are between 0 and 1
                for (int i=0; i <= iterations; ++i)
                {
                    hue += ((double)histogram[i]) / total;
                }

                green = pow(255, hue);
                blue = pow(255, hue);
            }

            bitmap.setPixel(x, y, red, green, blue);
        }
    }

    bitmap.write("test.bmp");

    std::cout << "Finished" << std::endl;

    return 0;
}