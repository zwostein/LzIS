#ifndef _MODEL_UPDATER_INCLUDED_
#define _MODEL_UPDATER_INCLUDED_


#include <Model/AUpdateable.hpp>

#include <memory>


namespace Model
{
	class Updater
	{
	public:
		Updater( AUpdateable & updateable );
		virtual ~Updater();

		double tick();

	private:
		class Impl;
		std::unique_ptr< Impl > pImpl;

		AUpdateable & updateable;
	};
}


#endif
