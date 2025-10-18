#include <algorithm>
#include <fstream>
#define CANVAS_ITY_IMPLEMENTATION // exactly define this. before include canvas_ity.hpp
#include "canvas_ity.hpp"
#include "./write_png.h"

using namespace canvas_ity;

int main () {
    const int height = 256;
    const int width = 256;


    //1. create 2dcontent
    canvas_ity::canvas context(width,height);
    context.fill_rectangle(1,1,100,100);
    //
    // Fetch the rendered RGBA pixels from the entire canvas.
    unsigned char *image = new unsigned char[ height * width * 4 ];
    context.get_image_data( image, width, height, width * 4, 0, 0 );
    write_png("helloworld.png",image,width,height);
    delete [] image;
    return 0;
}

