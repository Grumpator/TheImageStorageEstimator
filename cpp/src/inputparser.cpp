#include "inputparser.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "group.h"
#include "jpeg.h"
#include "jpeg2000.h"

using namespace SizeEstimator;

class InputParser::PrivateData {
public:
    PrivateData() :
            quit( false ),
            error( false ),
            errorStr( "" ),
            images(),
            groups()
    {}

    ~PrivateData()
    {
        for( unsigned i = 0; i < this->images.size(); ++ i ) {
            delete this->images[i];
        }
        this->images.clear();
        for( unsigned i = 0; i < this->groups.size(); ++ i ) {
            delete this->groups[i];
        }
        this->groups.clear();
    }

    bool        quit;
    bool        error;
    std::string errorStr;

    std::vector< Bitmap* >  images;
    std::vector< Group* >   groups;
};

InputParser::InputParser() :
        d( new PrivateData )
{
}

InputParser::~InputParser()
{
    delete this->d;
    this->d = NULL;
}

bool    InputParser::quit( void ) const
{
    return this->d->quit;
}

void    InputParser::parse( std::string input )
{
    this->d->error = false;
    this->d->errorStr = "";

    // convert to lowercase to make the input case insensitive
    std::transform( input.begin(), input.end(), input.begin(), ::tolower );
    // split the string into array by spaces
    std::vector< std::string > arr = this->stringToArray( input, ' ' );

    // at least on argument is required
    if( arr.size() < 1 ) {
        this->d->error = true;
        this->d->errorStr = "Not enough argumens.";
        return;
    }

    if( arr[0] == "q" ) {
        this->d->quit = true;
        return;
    } else if( arr[0] == "g" ) {
        this->groupImages( arr );
        return;
    }

    if( arr.size() < 3 ) {
        this->d->error = true;
        this->d->errorStr = "Not enough argumens.";
        return;
    } else if ( arr.size() > 3 ) {
        this->d->error = true;
        this->d->errorStr = "Too many argumens.";
        return;
    }

    this->addImage( arr );

}

int     InputParser::byteSize( void ) const
{
    int size = 0;
    for( unsigned i = 0; i < this->d->images.size(); ++ i ) {
        Bitmap* img = this->d->images[i];
        if( !img->isGroupMember() ) {
            size += img->byteSize();
        }
    }
    for( unsigned i = 0; i < this->d->groups.size(); ++ i ) {
        size += this->d->groups[i]->byteSize();
    }
    return size;
}

bool    InputParser::error( void ) const
{
    return this->d->error;
}

std::string InputParser::errorString( void ) const
{
    return this->d->errorStr;
}

void    InputParser::printHelp( void ) const
{
    std::cout << "Storage Calculator by I. AM." << std::endl;
    std::cout << "Enter one line for each image/group in the format:" << std::endl;
    std::cout << "type width hieght" << std::endl;
    std::cout << "G i, i, ..." << std::endl;
    std::cout << "Exit with 'q'" << std::endl;
    std::cout << std::endl;
}

void    InputParser::addImage( const std::vector< std::string >& arr )
{
    int width = atoi( arr[1].c_str() );
    int height = atoi( arr[2].c_str() );
    Bitmap* img = NULL;
    if( arr[0] == "bmp" ) {
        img = new Bitmap( width, height );
    } else if( arr[0] == "j" || arr[0] == "jpg" ) {
        img = new JPEG( width, height );
    } else if( arr[0] == "jp2" || arr[0] == "jpeg2000" ) {
        img = new JPEG2000( width, height );
    } else {
        this->d->error = true;
        this->d->errorStr = "Requested unknown image type [" + arr[0] + "]";
    }

    if( img != NULL ) {
        this->d->images.push_back( img );
    }
}

void    InputParser::groupImages( const std::vector< std::string >& arr )
{
    bool ok = true;

    Group* g = new Group();

    for( unsigned i = 1; ok && i < arr.size(); ++i ) {
        unsigned idx = atoi( arr[i].c_str() );
        if( idx > 0 && this->d->images.size() >= idx ) {
            ok = g->add( this->d->images[idx-1] );
        } else {
            ok = false;
        }
    }

    if( ok ) {
        this->d->groups.push_back( g );
    } else {
        this->d->error = true;
        this->d->errorStr = "Can't group the images.";
        g->clear();
        delete g;
    }
}

std::vector< std::string >  InputParser::stringToArray( const std::string& str, char delimiter ) const
{
    std::vector< std::string > arr;

    std::stringstream ss(str);
    std::string tmp;
    while( ss >> tmp ) {
        arr.push_back( tmp );
    }

    return arr;
}
