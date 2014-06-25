#ifndef _VIEW_RENDERER_ABATCHRENDERER_INCLUDED_
#define _VIEW_RENDERER_ABATCHRENDERER_INCLUDED_


#include <View/Renderer/ARenderable.hpp>


namespace View
{
	namespace Renderer
	{
		template< typename T >
		class ABatchRenderer : public ARenderable
		{
		public:
			virtual bool addModel( const T & model ) = 0;
			virtual bool removeModel( const T & model ) = 0;
		};
	}
}


#endif
