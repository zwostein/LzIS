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
				Shader( GLenum type, const std::string & source );
				~Shader();
			private:
				GLuint id;
			};
		}
	}
}


#endif
