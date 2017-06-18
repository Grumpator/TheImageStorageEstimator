#ifndef GROUP_H
#define GROUP_H

namespace SizeEstimator
{
    class Bitmap;

    class Group
    {
    public:
        Group();
        ~Group();

        bool    add( Bitmap* image );
        int     byteSize( void )    const;
        void    clear( void )       const;

    private:
        class PrivateData;
        PrivateData*    d;
    };
}
#endif // GROUP_H
