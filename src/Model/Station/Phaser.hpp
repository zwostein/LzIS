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
			class NewEvent : public AStation::NewEvent
			{
			public:
				NewEvent( const Phaser & phaser ) : AStation::NewEvent(phaser) {}
				const Phaser & getStation() const { return static_cast<const Phaser &>(AStation::NewEvent::getStation()); }
			protected:
				HIERARCHICAL_EVENT( AStation::NewEvent, NewEvent )
			};

			class DeleteEvent : public AStation::DeleteEvent
			{
			public:
				DeleteEvent( const Phaser & phaser ) : AStation::DeleteEvent(phaser) {}
				const Phaser & getStation() const { return static_cast<const Phaser &>(AStation::DeleteEvent::getStation()); }
			protected:
				HIERARCHICAL_EVENT( AStation::DeleteEvent, DeleteEvent )
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
