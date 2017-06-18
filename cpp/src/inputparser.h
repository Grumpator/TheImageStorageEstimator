#ifndef INPUTPARSER_H
#define INPUTPARSER_H

#include <string>
#include <vector>

namespace SizeEstimator
{
    class InputParser
    {
    public:
        InputParser();
        ~InputParser();

        bool    quit( void ) const;
        void    parse( std::string input );
        int     byteSize( void ) const;

        bool        error( void ) const;
        std::string errorString( void ) const;

        void        printHelp( void ) const;

    private:
        void    addImage( const std::vector< std::string >& arr );
        void    groupImages( const std::vector< std::string >& arr );
        std::vector< std::string >  stringToArray( const std::string& str, char delimiter ) const;

        class PrivateData;
        PrivateData*    d;
    };
}
#endif // INPUTPARSER_H
