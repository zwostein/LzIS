#ifndef _VIEW_RENDERER_GLES2_TEXTURE_INCLUDED_
#define _VIEW_RENDERER_GLES2_TEXTURE_INCLUDED_


#include <View/Renderer/GLES2/Error.hpp>

#include <View/RenderContext/GLES2.hpp>

#include <Resource/Image.hpp>

#include <GLES2/gl2.h>


namespace View
{
	namespace Renderer
	{
		namespace GLES2
		{
			class Texture2D
			{
			public:
				Texture2D( const Texture2D & ) = delete;
				Texture2D & operator=( const Texture2D & ) = delete;

				Texture2D();
				Texture2D( Resource::RGBAImage & image );
				virtual ~Texture2D();

				void load( Resource::RGBAImage & image );
				void bind() const
				{
					GLES2_ERROR_CHECK_UNHANDLED();
					glBindTexture( GL_TEXTURE_2D, this->id );
					GLES2_ERROR_CHECK("glBindTexture");
				}

			private:
				GLuint id = 0;
			};
		}
	}
}


#endif
