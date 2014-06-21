#ifndef _VIEW_ADRAWER_INCLUDED_
#define _VIEW_ADRAWER_INCLUDED_


#include "ADrawable.hpp"


namespace View
{
	class ADrawer : public ADrawable
	{
	public:
		virtual bool addDrawable( const ADrawable * drawable ) = 0;
		virtual bool removeDrawable( const ADrawable * drawable ) = 0;
	};
}


#endif
