#include <View/Renderer/GLES2/Texture2D.hpp>

#include <View/Renderer/GLES2/Error.hpp>


using namespace View;
using namespace View::Renderer::GLES2;


Texture2D::Texture2D()
{
}


Texture2D::Texture2D( Resource::RGBAImage & image )
{
	this->load( image );
}


Texture2D::~Texture2D()
{
	if( this->id )
		glDeleteTextures( 1, &this->id );
}


void Texture2D::load( Resource::RGBAImage & image )
{
	GLES2_ERROR_CHECK_UNHANDLED();
	if( this->id )
	{
		glDeleteTextures( 1, &this->id );
		GLES2_ERROR_CHECK("glDeleteTextures");
	}

	glGenTextures( 1, &this->id );
	GLES2_ERROR_CHECK("glGenTextures");
	glBindTexture( GL_TEXTURE_2D, this->id );
	GLES2_ERROR_CHECK("glBindTexture");
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getData() );
	GLES2_ERROR_CHECK("glTexImage2D");

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	GLES2_ERROR_CHECK("glTexParameteri");
}
