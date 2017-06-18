#ifndef BITMAP_H
#define BITMAP_H

#define MIN_PYRAMID_IMAGE_WIDTH  128
#define MIN_PYRAMID_IMAGE_HEIGHT 128

namespace SizeEstimator
{
    class Bitmap
    {
    public:
        enum Type {
            BMP,
            JPEG,
            JPEG2000,
        };

        Bitmap( int width, int height, Type type = BMP );
        ~Bitmap();
        int     width()     const;
        int     height()    const;
        int     type()      const;
        int     byteSize()  const;

        bool    isGroupMember( void ) const;
        void    setGroupMember( bool val );

    protected:
        void    setByteSize( int size );
        virtual int     calculateByteSize() const;

    private:
        class PrivateData;
        PrivateData*    d;
    };
}
#endif // BITMAP_H
