#ifndef _VIEW_RENDERER_ARENDERER_INCLUDED_
#define _VIEW_RENDERER_ARENDERER_INCLUDED_


#include "../ADrawable.hpp"


namespace View
{
	namespace Renderer
	{
		template< typename T >
		class ARenderer : public ADrawable
		{
		public:
			virtual bool addModel( const T & model ) = 0;
			virtual bool removeModel( const T & model ) = 0;
		};
	}
}


#endif
