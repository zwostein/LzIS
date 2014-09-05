#ifndef _MODEL_NET_PULSENODE_INCLUDED_
#define _MODEL_NET_PULSENODE_INCLUDED_


#include <Model/Net/Node.hpp>
#include <Model/Net/PulseLink.hpp>
#include <Model/AStepable.hpp>
#include <EventSystem.hpp>

#include <glm/vec2.hpp>

#include <iostream>
#include <set>


namespace Model
{
	namespace Net
	{
		class PulseNode : public Node< PulseNode, PulseLink >, public AStepable, public AutoEventSource
		{
		public:
			struct NewLinkEvent
			{
				NewLinkEvent( const PulseLink & link ) : link(link) {}
				const PulseLink & link;
			};

			struct DeleteLinkEvent
			{
				DeleteLinkEvent( const PulseLink & link ) : link(link) {}
				const PulseLink & link;
			};

			static PulseLink * setLink( PulseNode * source, PulseNode * other, PulseLink * link );

			PulseNode( EventHandler * eventHandler ) : AutoEventSource( eventHandler ) {}
			virtual ~PulseNode() {}

			const glm::vec2 & getPosition() const { return this->position; }
			void setPosition( const glm::vec2 & position ) { this->position = position; }

			float getRadius() const { return this->radius; }
			void setRadius( float radius ) { this->radius = radius; }

			unsigned int getOutLinkCapacity() const { return this->outLinkCapacity; }
			void setOutLinkCapacity( unsigned int outLinkCapacity ) { this->outLinkCapacity = outLinkCapacity; }

			unsigned int getInLinkCapacity() const { return this->inLinkCapacity; }
			void setInLinkCapacity( unsigned int inLinkCapacity ) { this->inLinkCapacity = inLinkCapacity; }

			virtual void step() override
			{
				for( auto & linkEntry : this->getOutLinks() )
				{
					PulseLink * link = linkEntry.second;
					link->pulse = false;
				}
			}

		private:
			glm::vec2 position;
			float radius = 1.0f;
			unsigned int outLinkCapacity = 4;
			unsigned int inLinkCapacity = 4;
		};
	}
}


#endif
