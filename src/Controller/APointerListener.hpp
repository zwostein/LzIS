#ifndef _CONTROLLER_APOINTERLISTENER_INCLUDED_
#define _CONTROLLER_APOINTERLISTENER_INCLUDED_


#include <glm/vec2.hpp>


namespace Controller
{
	struct PointerEvent;
	class APointerListener
	{
	public:
		virtual bool pointerEvent( const PointerEvent & event ) = 0;
	};
}


#endif
