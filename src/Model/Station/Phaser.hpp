#ifndef _MODEL_STATION_PHASER_INCLUDED_
#define _MODEL_STATION_PHASER_INCLUDED_


#include <Model/Station/AStation.hpp>
#include <Model/Net/APulseConsumer.hpp>


namespace Model
{
	namespace Station
	{
		class Phaser : public AStation, public Net::APulseConsumer
		{
		public:
			struct NewEvent
			{
				NewEvent( const Phaser & phaser ) : phaser(phaser) {}
				const Phaser & phaser;
			};

			struct DeleteEvent
			{
				DeleteEvent( const Phaser & phaser ) : phaser(phaser) {}
				const Phaser & phaser;
			};

			Phaser( EventHandler * eventHandler = nullptr );
			virtual ~Phaser();

			virtual void update( double delta ) override;

			virtual Net::PulseNode * getNode() override { return this->node; }
			virtual bool isPulseNeeded() const override { return this->pulses == 0; }
			virtual bool givePulse() override;
			virtual int getPriority() const override { return 0; }

			virtual void setPosition( const glm::vec2 & position ) override;
			virtual float getRadius() const override { return 10.0f; }

			void setPulses( unsigned int pulses ) { this->pulses = pulses; }

		private:
			Net::PulseNode * node = nullptr;
			unsigned int pulses = 0;
		};
	}
}

#endif
