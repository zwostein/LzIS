#ifndef _MODEL_ACIRCLE2D_INCLUDED_
#define _MODEL_ACIRCLE2D_INCLUDED_


#include <Model/APositionable2D.hpp>


namespace Model
{
	class ACircle2D : public APositionable2D
	{
	public:
		virtual float getRadius() const = 0;
		virtual void setRadius( float radius ) = 0;
	};
}


#endif
