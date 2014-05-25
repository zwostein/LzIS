#ifndef _MODEL_NET_PULSENODELINKER_INCLUDED_
#define _MODEL_NET_PULSENODELINKER_INCLUDED_


#include "PulseNode.hpp"


namespace Model
{
	namespace Net
	{
		class PulseNodeLinker
		{
		public:
			virtual bool link( PulseNode * source, PulseNode * other ) const;
			virtual bool unlink( PulseNode * source, PulseNode * other ) const;
		};
	}
}


#endif
