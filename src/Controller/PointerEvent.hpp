#ifndef _CONTROLLER_POINTEREVENT_INCLUDED_
#define _CONTROLLER_POINTEREVENT_INCLUDED_


#include <glm/vec2.hpp>


namespace Controller
{
	struct PointerDownEvent
	{
		unsigned int device = 0;
		unsigned int pointer = 0;
		unsigned int button = 0;
		glm::vec2 position;
		float pressure = 1.0f;
	};
	struct PointerUpEvent
	{
		unsigned int device = 0;
		unsigned int pointer = 0;
		unsigned int button = 0;
		glm::vec2 position;
	};
	struct PointerMotionEvent
	{
		unsigned int device = 0;
		unsigned int pointer = 0;
		glm::vec2 position;
		glm::vec2 delta;
		float pressure = 1.0f;
	};
}


#endif
