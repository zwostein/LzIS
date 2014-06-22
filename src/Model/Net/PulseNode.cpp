#include <Model/Net/PulseNode.hpp>


using namespace Model::Net;


PulseLink * PulseNode::setLink( PulseNode * source, PulseNode * other, PulseLink * link )
{
	if( link ) // if linking
	{
		if( source->getOutLinks().size() >= source->getOutLinkCapacity() )
			return nullptr; // abort if source can't take any more outgoing links
		if( other->getInLinks().size() >= other->getInLinkCapacity() )
			return nullptr; // abort if other node can't take any more incoming links
		link->from = source;
		link->to = other;
		link = Node< PulseNode, PulseLink >::setLink( source, other, link );
		if( link )
			source->dispatch( NewLinkEvent( *link ) );
		return link;
	}
	else
	{
		PulseLink * oldLink = Node< PulseNode, PulseLink >::setLink( source, other, nullptr );
		if( oldLink )
			source->dispatch( DeleteLinkEvent( *oldLink ) );
		return oldLink;
	}
}
