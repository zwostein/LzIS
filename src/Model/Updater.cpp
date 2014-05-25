#include "Updater.hpp"

#include <algorithm>


using namespace Model;


bool Updater::addUpdateable( AUpdateable * updateable )
{
	auto it = std::find( this->updateables.begin(), this->updateables.end(), updateable );
	if( it != this->updateables.end() )
		return false; // already added

	this->updateables.push_back( updateable );
	return true;
}


bool Updater::removeUpdateable( AUpdateable * updateable )
{
	auto it = std::find( this->updateables.begin(), this->updateables.end(), updateable );
	if( it == this->updateables.end() )
		return false; // not in list

	this->updateables.erase( it );
	return true;
}


void Updater::update( double delta )
{
	for( auto & updateable : this->updateables )
		updateable->update( delta );
}
