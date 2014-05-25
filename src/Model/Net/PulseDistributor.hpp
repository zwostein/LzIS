#ifndef _MODEL_NET_PULSEDISTRIBUTOR_INCLUDED_
#define _MODEL_NET_PULSEDISTRIBUTOR_INCLUDED_


#include "../AStepUpdateable.hpp"

#include <vector>


namespace Model
{
	namespace Net
	{
		class APulseProvider;
		class APulseConsumer;
		class PulseNode;
		class PulseLink;

		class PulseDistributor : public Model::AStepUpdateable
		{
		public:
			bool addNode( PulseNode * node );
			bool addProvider( APulseProvider * provider );
			bool addConsumer( APulseConsumer * consumer );
			bool removeNode( PulseNode * node );
			bool removeProvider( APulseProvider * provider );
			bool removeConsumer( APulseConsumer * consumer );
			virtual void step() override;
		private:
			std::vector< APulseProvider * > providers;
			std::vector< APulseConsumer * > consumers;
			std::vector< PulseNode * > nodes;
		};
	}
}


#endif
