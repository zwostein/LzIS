#ifndef _MODEL_AUPDATER_INCLUDED_
#define _MODEL_AUPDATER_INCLUDED_


#include "AUpdateable.hpp"


namespace Model
{
	class AUpdater : public AUpdateable
	{
	public:
		virtual bool addUpdateable( AUpdateable * updateable ) = 0;
		virtual bool removeUpdateable( AUpdateable * updateable ) = 0;
	};
}


#endif
