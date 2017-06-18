#ifndef JPEG2000_H
#define JPEG2000_H

#include "bitmap.h"

namespace SizeEstimator
{
    class JPEG2000 : public Bitmap
    {
    public:
        JPEG2000( int width, int height );

    protected:
        int     calculateByteSize() const;
    };
}
#endif // JPEG2000_H
