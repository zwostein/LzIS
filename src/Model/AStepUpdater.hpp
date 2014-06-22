#ifndef _MODEL_ASTEPUPDATER_INCLUDED_
#define _MODEL_ASTEPUPDATER_INCLUDED_


#include <Model/AStepUpdateable.hpp>


namespace Model
{
	class AStepUpdater
	{
	public:
		virtual bool addStepUpdateable( AStepUpdateable * stepUpdateable ) = 0;
		virtual bool removeStepUpdateable( AStepUpdateable * stepUpdateable ) = 0;
	};
}


#endif
