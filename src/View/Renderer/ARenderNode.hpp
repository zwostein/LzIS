#ifndef _VIEW_RENDERER_ARENDERNODE_INCLUDED_
#define _VIEW_RENDERER_ARENDERNODE_INCLUDED_


#include <View/Renderer/ARenderable.hpp>


namespace View
{
	namespace Renderer
	{
		class ARenderNode : public ARenderable
		{
		public:
			virtual bool addRenderable( const ARenderable * drawable ) = 0;
			virtual bool removeRenderable( const ARenderable * drawable ) = 0;
		};
	}
}


#endif
