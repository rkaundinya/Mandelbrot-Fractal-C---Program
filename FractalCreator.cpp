#include "./FractalCreator.h"

void FractalCreator::run (std::string name)
{
    addZoom(Zoom(295, m_height - 202, 0.1));
    addZoom(Zoom(312, m_height - 304, 0.1));
    //add(Zoom(399, m_height - 231, 0.1));
    //add(Zoom(59, m_height - 196, 0.1));
    calculateIteration();
    calculateTotalIterations();
    drawFractal();
    writeBitmap("test.bmp");
}

FractalCreator::FractalCreator (int width, int height) : m_width(width), 
    m_height(height), m_histogram(new int[Mandelbrot::MAX_ITERATIONS]{ 0 }), 
    m_fractal(new int[m_width*m_height] { 0 }), m_bitmap(m_width, m_height), 
    m_zoomList(m_width, m_height)
{
    m_zoomList.add(Zoom(m_width/2, height/2, 4.0/m_width));
}

FractalCreator::~FractalCreator()
{

}

void FractalCreator::calculateIteration()
{
    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            // Implement mandelbrot zoom on each coordinate to render image
            // for all pixels at current zoom level
            std::pair <double, double> coords = m_zoomList.doZoom(x,y);
            
            int iterations = Mandelbrot::getIterations(coords.first, coords.second);

            m_fractal[y * m_width + x] = iterations; 

            // Adds one to the index of the m_histogram corresponding to the number of 
            // iterations the current point reaches
            if (iterations != Mandelbrot::MAX_ITERATIONS)
            {
                m_histogram[iterations]++;
            }
        }
    }
}

void FractalCreator::calculateTotalIterations()
{
    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; ++i)
    {
        m_total += m_histogram[i];
    }
}

void FractalCreator::drawFractal()
{
    RGB startColor(0, 0, 0);
    RGB endColor(0, 140, 140);
    RGB colorDiff = endColor - startColor;

    for (int y = 0; y < m_height; ++y)
    {
        for (int x = 0; x < m_width; ++x)
        {
            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;

            // gets you num of iterations per current pixel
            int iterations = m_fractal[y * m_width + x];

            if (iterations != Mandelbrot::MAX_ITERATIONS)
            {
                double hue = 0.0;
                // This loop below increases the color of pixels which have 
                // the number of iterations the nested for loop is currently on.
                // Essentially adds a certian amount of color to each pixel
                // with the particular iteration type. Hue values are between 0 and 1
                for (int i=0; i <= iterations; ++i)
                {
                    hue += ((double)m_histogram[i]) / m_total;
                }

                red = startColor.r + colorDiff.r * hue;
                green = startColor.g + colorDiff.g * hue;
                blue = startColor.b + colorDiff.b * hue;

                /* red = startColor.r + pow(colorDiff.r, hue);
                green = startColor.g + pow(colorDiff.g, hue);
                blue = startColor.b + pow(colorDiff.b, hue);  */
            }

            m_bitmap.setPixel(x, y, red, green, blue);
        }
    }
}

void FractalCreator::addZoom(const Zoom& zoom)
{
    m_zoomList.add(zoom);
}

void FractalCreator::writeBitmap(std::string name)
{
    m_bitmap.write(name);
}