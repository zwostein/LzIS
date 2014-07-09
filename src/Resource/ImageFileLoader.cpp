#include <Resource/ImageFileLoader.hpp>


#include <stdexcept>

#include <stdlib.h>

#include <glm/fwd.hpp>
#include <glm/vec4.hpp>

#include <FreeImage.h>


#define RUNTIME_ERROR( whattext ) \
	std::runtime_error( std::string(__PRETTY_FUNCTION__) + std::string(": ") + (whattext) );


static bool initialise()
{
	atexit( FreeImage_DeInitialise );
	FreeImage_Initialise();
	return true;
}

static bool initialised = initialise();


static FIBITMAP * load( const std::string & fileName )
{
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType( fileName.c_str() );

	if( fif == FIF_UNKNOWN )
		fif = FreeImage_GetFIFFromFilename( fileName.c_str() );

	if( fif == FIF_UNKNOWN )
		throw RUNTIME_ERROR("Could not get filetype for \"" + fileName + "\"");

	if( !FreeImage_FIFSupportsReading(fif) )
		throw RUNTIME_ERROR("No decoder for \"" + fileName + "\"");

	FIBITMAP * dib =  FreeImage_Load( fif, fileName.c_str() );
	if( !dib )
		throw RUNTIME_ERROR("Cannot decode \"" + fileName + "\"");

	return dib;
}


namespace Resource
{
	template<>
	RGBAImage * ImageFileLoader::newFromFile( const std::string & fileName, bool convert )
	{
		FIBITMAP * dib = load( fileName );
		if( FreeImage_GetBPP( dib ) != 32 )
		{
			if( !convert )
				return nullptr;
			FIBITMAP * converted = FreeImage_ConvertTo32Bits( dib );
			FreeImage_Unload( dib );
			dib = converted;
		}

		RGBAImage * image = new RGBAImage( FreeImage_GetWidth( dib ), FreeImage_GetHeight( dib ) );

		//TODO: this is slow
		for( unsigned int y = 0; y < FreeImage_GetHeight( dib ); y++ )
		{
			for( unsigned int x = 0; x < FreeImage_GetWidth( dib ); x++ )
			{
				RGBQUAD color;
				FreeImage_GetPixelColor( dib, x, y, &color );
				image->at(x,y).r = color.rgbRed;
				image->at(x,y).g = color.rgbGreen;
				image->at(x,y).b = color.rgbBlue;
				image->at(x,y).a = color.rgbReserved;
			}
		}

		FreeImage_Unload( dib );
		return image;
	}
}
