#ifndef _RESOURCE_IMAGEFILELOADER_INCLUDED_
#define _RESOURCE_IMAGEFILELOADER_INCLUDED_


#include <string>

#include <Resource/Image.hpp>


namespace Resource
{
	class ImageFileLoader
	{
	public:
		template< typename TImageType >
		static TImageType * newFromFile( const std::string & fileName, bool convert = false );

	private:
		ImageFileLoader();
	};
}


#endif
