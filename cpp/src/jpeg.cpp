#include "jpeg.h"

using namespace SizeEstimator;

JPEG::JPEG( int width, int height ) :
    Bitmap( width, height, Bitmap::JPEG )
{
    this->setByteSize( this->calculateByteSize() );
}

int JPEG::calculateByteSize() const
{
    int size = 0;

    int w = this->width();
    int h = this->height();
    do {
        int pixels = w * h;
        size += pixels * 0.2;
        w /= 2;
        h /= 2;
    } while( w >= MIN_PYRAMID_IMAGE_WIDTH && h >= MIN_PYRAMID_IMAGE_HEIGHT );

    return size;
}
