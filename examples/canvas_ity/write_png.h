#include <string>
#include <fstream>
// Simple single-function PNG writer.  This writes perfectly valid,
// though uncompressed, PNG files from sRGBA8 image data, using deflate's
// uncompressed storage mode and wrapping it in a zlib and PNG container.
// There are much simpler formats for RGBA8 images, such as TGA, but support
// for reading the PNG format is nearly universal.
//
void write_png(
    std::string const &filename,
    unsigned char const *image,
    int width,
    int height )
{
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
