#include "PulseNode.hpp"


using namespace Model::Net;


bool PulseNode::setLink( PulseNode * source, PulseNode * other, PulseLink * link )
{
	if( link ) // if linking
	{
		if( source->getOutLinks().size() >= source->getOutLinkCapacity() )
			return false; // abort if source can't take any more outgoing links
		if( other->getInLinks().size() >= other->getInLinkCapacity() )
			return false; // abort if other node can't take any more incoming links
		link->from = source;
		link->to = other;
	}
	return Node< PulseNode, PulseLink >::setLink( source, other, link );
}
