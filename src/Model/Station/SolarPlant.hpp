#ifndef _MODEL_SOLARPLANT_INCLUDED_
#define _MODEL_SOLARPLANT_INCLUDED_


#include "AStation.hpp"
#include "../Net/APulseProvider.hpp"


namespace Model
{
	class SolarPlant : public AStation, public Net::APulseProvider
	{
	public:
		struct NewEvent
		{
			NewEvent( const SolarPlant & solarPlant ) : solarPlant(solarPlant) {}
			const SolarPlant & solarPlant;
		};

		struct DeleteEvent
		{
			DeleteEvent( const SolarPlant & solarPlant ) : solarPlant(solarPlant) {}
			const SolarPlant & solarPlant;
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


#endif
