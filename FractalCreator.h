#ifndef FRACTAL_CREATOR_H
#define FRACTAL_CREATOR_H

#include <string>
#include <math.h>
#include "./Bitmap.h"
#include "./Zoom.h"
#include "./ZoomList.h"
#include "./Mandelbrot.h"
#include "./RGB.h"

class FractalCreator
{
    private: 
        int m_width; 
        int m_height;
        std::unique_ptr<int[]> m_histogram;
        std::unique_ptr<int[]> m_fractal;
        Bitmap m_bitmap;
        ZoomList m_zoomList; 
        int m_total {0};

        void calculateIteration();
        void drawFractal();
        void calculateTotalIterations();
        void addZoom(const Zoom& zoom);
        void writeBitmap(std::string name);

    public: 
        FractalCreator(int width, int height);
        virtual ~FractalCreator();
        void run (std::string name);
};

#endif