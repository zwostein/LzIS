#ifndef _CONTROLLER_POINTEREVENT_INCLUDED_
#define _CONTROLLER_POINTEREVENT_INCLUDED_


#include <glm/vec2.hpp>


namespace Controller
{
	struct PointerEvent
	{
		enum Type
		{
			DOWN,
			UP,
			MOTION,
		};
		Type type = MOTION;
		unsigned int device = 0;
		unsigned int point = 0;
		unsigned int button = 0;
		glm::vec2 position;
		glm::vec2 movement;
		glm::vec2 drag;
		float pressure = 0.0f;
	};
}


#endif
