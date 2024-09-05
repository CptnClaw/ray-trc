#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <string>
#include "viewport.h"

class Image
{
    public:
        static bool drawPPM(const std::string &filename, const Viewport &view);
};

#endif // _IMAGE_H_