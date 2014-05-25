#ifndef _MODEL_APOSITIONABLE2D_INCLUDED_
#define _MODEL_APOSITIONABLE2D_INCLUDED_


#include <glm/vec2.hpp>


namespace Model
{
	class APositionable2D
	{
	public:
		virtual glm::vec2 getPosition() const = 0;
		virtual void setPosition( const glm::vec2 & position ) = 0;
	};
}


#endif
