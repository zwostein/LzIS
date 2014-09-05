#ifndef _VIEW_RENDERCONTEXT_GLES2_INCLUDED_
#define _VIEW_RENDERCONTEXT_GLES2_INCLUDED_


#include <View/RenderContext//ARenderContext.hpp>


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

		private:
		};
	}
}


#endif
