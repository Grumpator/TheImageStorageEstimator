#ifndef JPEG_H
#define JPEG_H

#include "bitmap.h"

namespace SizeEstimator
{
    class JPEG : public Bitmap
    {
    public:
        JPEG( int width, int height );

    protected:
        int     calculateByteSize() const;
    };
}
#endif // JPEG_H
