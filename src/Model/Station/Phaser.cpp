#include <Model/Station/Phaser.hpp>

#include <Model/EventSystem.hpp>
#include <Model/Net/PulseNode.hpp>


using namespace Model::Station;


Phaser::Phaser( EventHandler * eventHandler ) : AStation(eventHandler)
{
	this->node = new Net::PulseNode( eventHandler );
	node->setInLinkCapacity( 4 );
	node->setOutLinkCapacity( 4 );
	this->dispatch( NewEvent(*this) );
}


Phaser::~Phaser()
{
	this->dispatch( DeleteEvent(*this) );
	delete this->node;
}


void Phaser::setPosition( const glm::vec2 & position )
{
	AStation::setPosition( position );
	this->node->setPosition( position );
}


bool Phaser::givePulse()
{
	this->pulses = 1;
	return true;
}


void Phaser::update( double delta )
{

}
