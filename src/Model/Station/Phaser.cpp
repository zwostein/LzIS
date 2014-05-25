#include "Phaser.hpp"

#include "../Net/PulseNode.hpp"


using namespace Model;


Phaser::Phaser()
{
	this->node = new Net::PulseNode;
	node->setInLinkCapacity( 4 );
	node->setOutLinkCapacity( 4 );
}


Phaser::~Phaser()
{
	delete this->node;
}


void Phaser::update( double delta )
{

}
