#ifndef _VIEW_RENDERCONTEXT_GLES2_INCLUDED_
#define _VIEW_RENDERCONTEXT_GLES2_INCLUDED_


#include <View/RenderContext/ARenderContext.hpp>

#include <GLES2/gl2.h>

#include <glm/gtc/matrix_transform.hpp>


namespace View
{
	namespace RenderContext
	{
		class GLES2 : public ARenderContext
		{
		public:
			GLES2( EventHandler * eventHandler ) :
				ARenderContext(eventHandler)
			{}

			virtual ~GLES2()
			{}

			virtual std::string getName() const override { return "OpenGL ES 2"; }

			virtual void resize( unsigned int width, unsigned int height ) override
			{
				glViewport( 0, 0, width, height );

				unsigned int size = std::min( width, height );
				float border = 0.5f * fabs( (double)width/(double)size - (double)height/(double)size );
				if( width > height )
					projection = glm::ortho(-1.0f - border, 1.0f + border,-1.0f, 1.0f,-1.0f, 1.0f );
				else
					projection = glm::ortho(-1.0f, 1.0f,-1.0f - border, 1.0f + border,-1.0f, 1.0f );
			}

			const glm::mat4 & getProjection() const { return this->projection; }

		private:
			glm::mat4 projection;
		};
	}
}


#endif
