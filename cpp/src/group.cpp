#include "group.h"

#include <vector>
#include <math.h>

#include "bitmap.h"

using namespace SizeEstimator;

class Group::PrivateData {
public:
    PrivateData() :
            byteSize( 0 ),
            images()
    {}
    int byteSize;

    std::vector< Bitmap* >  images;
};

Group::Group() :
        d( new PrivateData() )
{
}

Group::~Group()
{
    delete this->d;
    this->d = 0;
}

bool    Group::add( Bitmap* image )
{
    bool ret = false;
    if( !image->isGroupMember() ) {
        ret = true;
        image->setGroupMember( true );
        this->d->images.push_back( image );
    }
    return ret;
}

int Group::byteSize( void ) const
{
    int size = 0;
    if( this->d->images.size() > 0 ) {
        for( unsigned i = 0; i < this->d->images.size(); ++i ) {
            size += this->d->images[i]->byteSize();
        }
        size /= log( this->d->images.size()+3 );
    }

    return size;
}

void    Group::clear( void ) const
{
    for( unsigned i = 0; i < this->d->images.size(); ++i ) {
        this->d->images[i]->setGroupMember( false );
    }
}
