#ifndef _VIEW_RENDERCONTEXT_GLES2_INCLUDED_
#define _VIEW_RENDERCONTEXT_GLES2_INCLUDED_


#include <View/RenderContext//ARenderContext.hpp>


namespace View
{
	namespace RenderContext
	{
		class OpenAL : public ARenderContext
		{
		public:
			OpenAL( EventHandler * eventHandler ) :
				ARenderContext(eventHandler)
			{}

			virtual ~OpenAL()
			{}

			virtual std::string getName() const override { return "OpenAL"; }

		private:
		};
	}
}


#endif
