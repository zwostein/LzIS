#include "SolarPlant.hpp"

#include "../Net/PulseNode.hpp"


using namespace Model;


SolarPlant::SolarPlant()
{
	this->node = new Net::PulseNode;
	node->setInLinkCapacity( 0 );
	node->setOutLinkCapacity( 3 );
}


SolarPlant::~SolarPlant()
{
	delete this->node;
}


void SolarPlant::update( double delta )
{

}
