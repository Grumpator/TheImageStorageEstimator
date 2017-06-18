#include "jpeg2000.h"

#include <math.h>

using namespace SizeEstimator;

JPEG2000::JPEG2000( int width, int height ) :
    Bitmap( width, height, Bitmap::JPEG2000 )
{
    this->setByteSize( this->calculateByteSize() );
}

int JPEG2000::calculateByteSize() const
{
    int pixels = this->width() * this->height();
    int size = pixels * 0.4 / log( log ( pixels + 16 ) );
    return size;
}
