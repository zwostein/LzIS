#include "PulseNodeLinker.hpp"
#include "PulseNode.hpp"
#include "PulseLink.hpp"


using namespace Model::Net;


bool PulseNodeLinker::link( PulseNode * source, PulseNode * other ) const
{
	if( !source || !other || (source==other) )
		return false; // source node and destination node have to exist and must not be the same

	if( source->getOutLinkCapacity() <= source->getOutLinks().size() )
		return false; // source node can't take any more outgoing links

	if( other->getInLinkCapacity() <= other->getInLinks().size() )
		return false; // other node can't take any more links

	PulseLink * newLink = new PulseLink;
	PulseNode::setLink( source, other, newLink );

	return true;
}


bool PulseNodeLinker::unlink( PulseNode * source, PulseNode * other ) const
{
	const PulseLink * oldLink = source->getOutLink( other );
	PulseNode::setLink( source, other, nullptr );
	if( oldLink )
	{
		delete oldLink;
		return true;
	}
	else
	{
		return false;
	}
}
