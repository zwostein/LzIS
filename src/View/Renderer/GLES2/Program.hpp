#ifndef _VIEW_RENDERER_GLES2_PROGRAM_INCLUDED_
#define _VIEW_RENDERER_GLES2_PROGRAM_INCLUDED_


#include <View/Renderer/GLES2/Shader.hpp>
#include <View/Renderer/GLES2/Error.hpp>

#include <string>

#include <GLES2/gl2.h>


namespace View
{
	namespace Renderer
	{
		namespace GLES2
		{
			class Program
			{
			public:
				Program( const Program & ) = delete;
				Program & operator=( const Program & ) = delete;

				Program();
				virtual ~Program();

				void create();
				void attach( const Shader & shader );
				void link();

				GLint getAttributeLocation( const std::string & name ) const;
				GLint getUniformLocation( const std::string & name ) const;

				void use() const
				{
					GLES2_ERROR_CHECK_UNHANDLED();
					glUseProgram( this->id );
					GLES2_ERROR_CHECK("glUseProgram");
				}

			private:
				GLuint id = 0;
			};
		}
	}
}


#endif
