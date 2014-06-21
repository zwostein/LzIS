#ifndef _VIEW_RENDERER_ARENDERCONTEXT_INCLUDED_
#define _VIEW_RENDERER_ARENDERCONTEXT_INCLUDED_


#include <string>


namespace View
{
	namespace Renderer
	{
		class ARenderContext
		{
		public:
			virtual std::string getName() const = 0;
		};
	}
}


#endif
