#include <Model/Updater.hpp>

#include <SDL.h>


using namespace Model;


class Updater::Impl
{
public:
	unsigned int lastTime = 0;
};


Updater::Updater( Model::AUpdateable & updateable ) : pImpl(new Impl), updateable(updateable)
{
	if( !SDL_WasInit( SDL_INIT_TIMER ) )
		SDL_InitSubSystem( SDL_INIT_TIMER );
}


Updater::~Updater()
{
}


double Updater::tick()
{
	unsigned int currentTime = SDL_GetTicks();
	double delta = (currentTime - this->pImpl->lastTime) / 1000.0;
	this->pImpl->lastTime = currentTime;

	this->updateable.update( delta );
	return delta;
}
