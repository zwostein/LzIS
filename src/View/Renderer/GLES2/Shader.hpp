#ifndef _VIEW_RENDERER_GLES2_SHADER_INCLUDED_
#define _VIEW_RENDERER_GLES2_SHADER_INCLUDED_


#include <string>

#include <GLES2/gl2.h>


namespace View
{
	namespace Renderer
	{
		namespace GLES2
		{
			class Shader
			{
			public:
				Shader( const Shader & ) = delete;
				Shader & operator=( const Shader & ) = delete;

				Shader();
				Shader( GLenum type, const std::string & source );
				virtual ~Shader();

				void load( GLenum type, const std::string & source );
				GLuint getID() const { return this->id; }

			private:
				GLuint id = 0;
			};
		}
	}
}


#endif
