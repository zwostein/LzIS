#ifndef _MODEL_ABOUNDINGBOX2D_INCLUDED_
#define _MODEL_ABOUNDINGBOX2D_INCLUDED_


#include <glm/vec2.hpp>


namespace Model
{
	class ABoundingBox2D
	{
	public:
		virtual glm::vec2 getMinCorner() const = 0;
		virtual glm::vec2 getMaxCorner() const = 0;
	};
}


#endif
