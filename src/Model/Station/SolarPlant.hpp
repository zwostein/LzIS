#ifndef _MODEL_STATION_SOLARPLANT_INCLUDED_
#define _MODEL_STATION_SOLARPLANT_INCLUDED_


#include <Model/Station/AStation.hpp>
#include <Model/Net/APulseProvider.hpp>


namespace Model
{
	namespace Station
	{
		class SolarPlant : public AStation, public Net::APulseProvider
		{
		public:
			struct NewEvent : public AStation::NewEvent
			{
				NewEvent( const SolarPlant & solarPlant ) : AStation::NewEvent(solarPlant) {}
				const SolarPlant & getStation() const { return static_cast<const SolarPlant &>(AStation::NewEvent::getStation()); }
			protected:
				HIERARCHICAL_EVENT( AStation::NewEvent, NewEvent )
			};

			struct DeleteEvent : public AStation::DeleteEvent
			{
				DeleteEvent( const SolarPlant & solarPlant ) : AStation::DeleteEvent(solarPlant) {}
				const SolarPlant & getStation() const { return static_cast<const SolarPlant &>(AStation::DeleteEvent::getStation()); }
			protected:
				HIERARCHICAL_EVENT( AStation::DeleteEvent, DeleteEvent )
			};

			SolarPlant( EventHandler * eventHandler = nullptr );
			virtual ~SolarPlant();

			virtual void update( double delta ) override;

			virtual Net::PulseNode * getNode() override { return this->node; }
			virtual bool isPulseAvailable() const override { return this->pulses; }
			virtual bool takePulse() override;

			virtual void setPosition( const glm::vec2 & position ) override;
			virtual float getRadius() const override { return 20.0f; }

			void setPulses( unsigned int pulses ) { this->pulses = pulses; }

		private:
			Net::PulseNode * node = nullptr;
			unsigned int pulses = 0;
		};
	}
}


#endif
