#include "inputparser.h"

#include <iostream>

void sanityTest();

int main( int argc, char *argv[] )
{
    if( argc > 1 && std::string( argv[1] ) == "/t" ) {
        sanityTest();
        return 0;
    }

    SizeEstimator::InputParser ip;
    ip.printHelp();

    std::string input;
    while( !ip.quit() )
    {
        std::getline( std::cin, input );
        ip.parse( input );
        if( ip.error() ) { std::cout << "ERROR: " << ip.errorString() << std::endl; }
    }

    std::cout << "Size: " << ip.byteSize() << " bytes." << std::endl;

    return 0;
}

void    sanityTest( void )
{
    SizeEstimator::InputParser ip;

    ip.parse( "J 2048 1024" );
    if( ip.error() ) { std::cout << ip.errorString() << std::endl; }
    ip.parse( "JPG 5000 3000" );
    if( ip.error() ) { std::cout << ip.errorString() << std::endl; }
    ip.parse( "G 1 2" );
    if( ip.error() ) { std::cout << ip.errorString() << std::endl; }
    ip.parse( "JP2 1000 2000" );
    if( ip.error() ) { std::cout << ip.errorString() << std::endl; }
    ip.parse( "BMP 2000 1000" );
    if( ip.error() ) { std::cout << ip.errorString() << std::endl; }
    ip.parse( "q" );
    if( ip.error() ) { std::cout << ip.errorString() << std::endl; }

    std::cout << "Actual Size   : " << ip.byteSize() << " bytes." << std::endl;
    std::cout << "Expected Size : 5753091 bytes." << std::endl;
    std::cout << "Result        : " << ( ip.byteSize() == 5753091 ? "OK" : "WRONG" ) << std::endl;
}
