#include "SolarPlant.hpp"
#include "../EventSystem.hpp"
#include "../NewObjectEvent.hpp"
#include "../DeleteObjectEvent.hpp"
#include "../Net/PulseNode.hpp"


using namespace Model;


SolarPlant::SolarPlant( EventHandler * eventHandler ) : AStation(eventHandler)
{
	this->node = new Net::PulseNode;
	node->setInLinkCapacity( 0 );
	node->setOutLinkCapacity( 3 );
	this->dispatch( NewEvent(*this) );
}


SolarPlant::~SolarPlant()
{
	this->dispatch( DeleteEvent(*this) );
	delete this->node;
}


void SolarPlant::setPosition( const glm::vec2 & position )
{
	AStation::setPosition( position );
	this->node->setPosition( position );
}


bool SolarPlant::takePulse()
{
	if( !pulses )
		return false;
	pulses--;
	return true;
}


void SolarPlant::update( double delta )
{

}
