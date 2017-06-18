#include "bitmap.h"

using namespace SizeEstimator;

class Bitmap::PrivateData {
public:
    PrivateData() :
        isGroupMember( false ),
        type( Bitmap::BMP  ),
        width( 0 ),
        height( 0 ),
        byteSize( 0 )
    {}

    bool        isGroupMember;
    Bitmap::Type   type;
    int         width;
    int         height;
    int         byteSize;
};

Bitmap::Bitmap( int width, int height, Type type ) :
        d( new PrivateData() )
{
    this->d->width      = width;
    this->d->height     = height;
    this->d->type       = type;
    if( type == BMP ) {
        this->setByteSize( this->calculateByteSize() );
    }
}

Bitmap::~Bitmap()
{
    delete this->d;
    this->d = 0;
}

int Bitmap::width()     const
{
    return this->d->width;
}

int Bitmap::height()    const
{
    return this->d->height;
}

int Bitmap::type()      const
{
    return this->d->type;
}

int Bitmap::byteSize()      const
{
    return this->d->byteSize;
}

bool    Bitmap::isGroupMember( void ) const
{
    return this->d->isGroupMember;
}

void    Bitmap::setGroupMember( bool val )
{
    this->d->isGroupMember = val;
}

void    Bitmap::setByteSize( int size )
{
    this->d->byteSize = size;
}

int Bitmap::calculateByteSize() const
{
    int size = 0;

    int w = this->width();
    int h = this->height();
    do {
        int pixels = w * h;
        size += pixels;
        w /= 2;
        h /= 2;
    } while( w >= MIN_PYRAMID_IMAGE_WIDTH && h >= MIN_PYRAMID_IMAGE_HEIGHT );

    return size;
}
