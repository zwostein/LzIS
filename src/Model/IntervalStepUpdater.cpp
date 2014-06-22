#include <Model/IntervalStepUpdater.hpp>

#include <algorithm>


using namespace Model;


bool IntervalStepUpdater::addStepUpdateable( AStepUpdateable * stepUpdateable )
{
	auto it = std::find( this->stepUpdateables.begin(), this->stepUpdateables.end(), stepUpdateable );
	if( it != this->stepUpdateables.end() )
		return false; // already added

	this->stepUpdateables.push_back( stepUpdateable );
	return true;
}


bool IntervalStepUpdater::removeStepUpdateable( AStepUpdateable * stepUpdateable )
{
	auto it = std::find( this->stepUpdateables.begin(), this->stepUpdateables.end(), stepUpdateable );
	if( it == this->stepUpdateables.end() )
		return false; // not in list

	this->stepUpdateables.erase( it );
	return true;
}


void IntervalStepUpdater::update( double delta )
{
	this->elapsed += delta;
	while( this->elapsed >= this->interval )
	{
		this->elapsed -= this->interval;
		for( auto & stepUpdateable : this->stepUpdateables )
			stepUpdateable->step();
	}
}
