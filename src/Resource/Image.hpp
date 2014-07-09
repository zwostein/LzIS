#ifndef _RESOURCE_IMAGE_INCLUDED_
#define _RESOURCE_IMAGE_INCLUDED_


#include <vector>
#include <typeindex>

#include <string.h>

#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


namespace Resource
{
	template< typename TPixelType >
	class Image
	{
	public:
		typedef TPixelType PixelType;

		Image( unsigned int width, unsigned int height ) :
			width(width), height(height),
			data(width*height)
		{
		}

		Image( unsigned int width, unsigned int height, const TPixelType * data ) :
			width(width), height(height),
			data(width*height)
		{
			memcpy( this->data.data(), data, sizeof(TPixelType)*width*height );
		}

		unsigned int getWidth() const { return this->width; }
		unsigned int getHeight() const { return this->height; }

		const TPixelType * getData() const { return this->data.data(); }
		TPixelType * getData() { return this->data.data(); }

		const TPixelType & at( unsigned int x, unsigned int y ) const { return data[ x + width * y]; }
		TPixelType & at( unsigned int x, unsigned int y ) { return data[ x + width * y]; }

	private:
		unsigned int width;
		unsigned int height;
		std::vector<TPixelType> data;
	};

	typedef Image< glm::u8vec4 > RGBAImage;
	typedef Image< glm::u8vec3 > RGBImage;
	typedef Image< glm::u8vec1 > GreyscaleImage;
}


#endif
