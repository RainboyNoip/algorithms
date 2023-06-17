#include <string_view>
#include <string>
#include <memory>
#include <fstream>
#include "font.hpp"
#define CANVAS_ITY_IMPLEMENTATION
#include "canvas_ity.hpp"

using namespace canvas_ity;


static int const width = 2024, height = 1024;
static int const R = 20; //圆的半径
static float pi = 3.1415926;
struct Draw_Tree {

    canvas_ity::canvas context;

    Draw_Tree() : context(width,height)
    {}

    void set_default_font(){
        if( !font_a.empty() ) {
            context.set_font(font_a.data(), (int)font_a.size() , 40);
        }
    }

    //绘制一个点
    void draw_one_node(float x,float y,char N){
        context.begin_path();
        context.arc(x, y, R, 0, 2*pi);
        // context.close_path();
        context.set_color(fill_style , 1, 1, 1,1.0f);
        context.fill();
        // context.stroke();
        char buff[2] = {0};
        buff[0] = N;
        draw_text(buff, x, y);
    }

    void draw_text(const char * txt,float x,float y){
         context.text_align = canvas_ity::center;
        context.set_color(fill_style , 0, 0, 0,1.0f);
        context.fill_text(txt, x,y+10);
    }

    //绘制点的两个坐标信息
    void draw_node_info(float info1,float info2){

    }

    //绘制一条线
    void draw_line(float x1,float y1,float x2, float y2) {
        context.begin_path();
        context.move_to(x1, y1);
        context.line_to(x2, y2);
        context.set_color(stroke_style, 1, 1, 1, 1.0f);
        context.stroke();
    }

    //保存成png图片
    void save_to_png(const char * filename) {

    }
    void write_png(std::string const & filename) {
        unsigned char * image = new unsigned char [4 * width*height];
        context.get_image_data(image, width, height, 4*width, 0, 0);
        __write_png(filename, image, width, height);
        delete [] image;
    }
    // 分摊
    //
    // Simple single-function PNG writer.  This writes perfectly valid,
// though uncompressed, PNG files from sRGBA8 image data, using deflate's
// uncompressed storage mode and wrapping it in a zlib and PNG container.
// There are much simpler formats for RGBA8 images, such as TGA, but support
// for reading the PNG format is nearly universal.
//
    void __write_png(
            std::string const &filename,
            unsigned char const *image,
            int width,
            int height
            )
    {
        // unsigned char * image = new unsigned char [4 * width*height];
        // // std::unique_ptr<imageType> a = nullptr;
        // // a.reset(reinterpret_cast<imageType*>(image));
        

        std::ofstream output( filename.c_str(), std::ios::binary );
        unsigned table[ 256 ];
        for ( unsigned index = 0; index < 256; ++index )
        {
            unsigned value = index;
            for ( int step = 0; step < 8; ++step )
                value = ( value & 1 ? 0xedb88320u : 0u ) ^ ( value >> 1 );
            table[ index ] = value;
        }
        int idat_size = 6 + height * ( 6 + width * 4 );
        unsigned char header[] =
        {
            /*  0 */ 137, 80, 78, 71, 13, 10, 26, 10,                 // Signature
            /*  8 */ 0, 0, 0, 13, 73, 72, 68, 82,                     // IHDR
            /* 16 */ static_cast< unsigned char >( width  >> 24 ),
            /* 17 */ static_cast< unsigned char >( width  >> 16 ),
            /* 18 */ static_cast< unsigned char >( width  >>  8 ),
            /* 19 */ static_cast< unsigned char >( width  >>  0 ),
            /* 20 */ static_cast< unsigned char >( height >> 24 ),
            /* 21 */ static_cast< unsigned char >( height >> 16 ),
            /* 22 */ static_cast< unsigned char >( height >>  8 ),
            /* 23 */ static_cast< unsigned char >( height >>  0 ),
            /* 24 */ 8, 6, 0, 0, 0,
            /* 29 */ 0, 0, 0, 0,
            /* 33 */ 0, 0, 0, 1, 115, 82, 71, 66,                     // sRGB
            /* 41 */ 0,
            /* 42 */ 174, 206, 28, 233,
            /* 46 */ static_cast< unsigned char >( idat_size >> 24 ), // IDAT
            /* 47 */ static_cast< unsigned char >( idat_size >> 16 ),
            /* 48 */ static_cast< unsigned char >( idat_size >>  8 ),
            /* 49 */ static_cast< unsigned char >( idat_size >>  0 ),
            /* 50 */ 73, 68, 65, 84,
            /* 54 */ 120, 1,
        };
        unsigned crc = ~0u;
        for ( int index = 12; index < 29; ++index )
            crc = table[ ( crc ^ header[ index ] ) & 0xff ] ^ ( crc >> 8 );
        header[ 29 ] = static_cast< unsigned char >( ~crc >> 24 );
        header[ 30 ] = static_cast< unsigned char >( ~crc >> 16 );
        header[ 31 ] = static_cast< unsigned char >( ~crc >>  8 );
        header[ 32 ] = static_cast< unsigned char >( ~crc >>  0 );
        output.write( reinterpret_cast< char * >( header ), 56 );
        crc = ~0u;
        for ( int index = 50; index < 56; ++index )
            crc = table[ ( crc ^ header[ index ] ) & 0xff ] ^ ( crc >> 8 );
        int check_1 = 1;
        int check_2 = 0;
        int row_size = 1 + width * 4;
        for ( int y = 0; y < height; ++y, image += width * 4 )
        {
            unsigned char prefix[] = {
                /* 0 */ static_cast< unsigned char >( y + 1 == height ),
                /* 1 */ static_cast< unsigned char >(  ( row_size >> 0 ) ),
                /* 2 */ static_cast< unsigned char >(  ( row_size >> 8 ) ),
                /* 3 */ static_cast< unsigned char >( ~( row_size >> 0 ) ),
                /* 4 */ static_cast< unsigned char >( ~( row_size >> 8 ) ),
                /* 5 */ 0,
            };
            output.write( reinterpret_cast< char * >( prefix ), 6 );
            for ( int index = 0; index < 6; ++index )
                crc = table[ ( crc ^ prefix[ index ] ) & 0xff ] ^ ( crc >> 8 );
            output.write( reinterpret_cast< char const * >( image ), width * 4 );
            check_2 = ( check_2 + check_1 ) % 65521;
            for ( int index = 0; index < width * 4; ++index )
            {
                check_1 = ( check_1 + image[ index ] ) % 65521;
                check_2 = ( check_2 + check_1 ) % 65521;
                crc = table[ ( crc ^ image[ index ] ) & 0xff ] ^ ( crc >> 8 );
            }
        }
        unsigned char footer[] = {
            /*  0 */ static_cast< unsigned char >( check_2 >> 8 ),
            /*  1 */ static_cast< unsigned char >( check_2 >> 0 ),
            /*  2 */ static_cast< unsigned char >( check_1 >> 8 ),
            /*  3 */ static_cast< unsigned char >( check_1 >> 0 ),
            /*  4 */ 0, 0, 0, 0,
            /*  8 */ 0, 0, 0, 0, 73, 69, 78, 68,                      // IEND
            /* 16 */ 174, 66, 96, 130,
        };
        for ( int index = 0; index < 4; ++index )
            crc = table[ ( crc ^ footer[ index ] ) & 0xff ] ^ ( crc >> 8 );
        footer[ 4 ] = static_cast< unsigned char >( ~crc >> 24 );
        footer[ 5 ] = static_cast< unsigned char >( ~crc >> 16 );
        footer[ 6 ] = static_cast< unsigned char >( ~crc >>  8 );
        footer[ 7 ] = static_cast< unsigned char >( ~crc >>  0 );
        output.write( reinterpret_cast< char * >( footer ), 20 );

    }
};
