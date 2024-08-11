#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <iostream>
#include "viewport.h"
#include "tracer.h"

class Image
{
    public:
        Image(const std::string &filename, Tracer *tracer, Viewport *view);

        // Returns false is there as an error opening the file
        bool render() const;
        
    private:
        std::string filename;
        Tracer *tracer;
        Viewport *view;
        int width;
        int height;
};

#endif // _IMAGE_H_