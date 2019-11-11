#ifndef FRACTAL_CREATOR_H
#define FRACTAL_CREATOR_H

#include <string>
#include "./Zoom.h"

class FractalCreator
{
    public: 
        FractalCreator(int width, int height);
        virtual ~FractalCreator();

        void calculateIteration();
        void drawFractal();
        void addZoom(const Zoom& zoom);
        void writeBitmap(std::string name);
};

#endif