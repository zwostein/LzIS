#ifndef _MODEL_UPDATER_INCLUDED_
#define _MODEL_UPDATER_INCLUDED_


#include <Model/AUpdater.hpp>
#include <Model/AUpdateable.hpp>

#include <vector>


namespace Model
{
	class Updater : public AUpdater
	{
	public:
		virtual bool addUpdateable( AUpdateable * updateable ) override;
		virtual bool removeUpdateable( AUpdateable * updateable ) override;
		virtual void update( double delta ) override;
	private:
		std::vector< AUpdateable * > updateables;
	};
}


#endif
