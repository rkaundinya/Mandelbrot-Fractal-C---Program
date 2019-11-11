#include <complex>
#include "./Mandelbrot.h"

Mandelbrot::Mandelbrot()
{

}

Mandelbrot::~Mandelbrot()
{

}

int Mandelbrot::getIterations(double x, double y)
{
    std::complex<double> z = 0;
    std::complex<double> c(x, y);

    int iterations = 0;

    while (iterations < MAX_ITERATIONS)
    {
        z = z*z + c;

        // abs gets you the magnitude of a complex number - defined as distance from 0 
        // to the complex number coordinate
        // For some numbers, no matter how many times you do the calculation above, 
        // they will never exceed 2. But for others, they will and those are part of the 
        // mandelbrot set. Number of iterations it takes to get a value above 2 is 
        // what we will map to a color and makes cool fractal patterns
        if (abs(z) > 2)
        {
            break;
        }

        ++iterations;
    }

    return iterations;
}