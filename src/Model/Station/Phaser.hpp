#ifndef _MODEL_PHASER_INCLUDED_
#define _MODEL_PHASER_INCLUDED_


#include "../APositionable2D.hpp"
#include "../ABoundingBox2D.hpp"
#include "../AUpdateable.hpp"
#include "../Net/APulseConsumer.hpp"
#include "../Net/PulseNode.hpp"


namespace Model
{
	class Phaser : public AUpdateable, public Net::APulseConsumer, public APositionable2D, public ABoundingBox2D
	{
	public:
		Phaser();
		virtual ~Phaser();

		virtual void update( double delta ) override;

		virtual Net::PulseNode * getNode() override { return this->node; }
		virtual bool isPulseNeeded() const override { return this->pulses == 0; }
		virtual bool givePulse() { this->pulses = 1; return true; }
		virtual int getPriority() const override { return 0; }
		virtual glm::vec2 getPosition() const { return this->position; }
		virtual void setPosition( const glm::vec2 & position ) { this->position = position; this->node->setPosition( position ); }
		virtual glm::vec2 getMaxCorner() const { return this->position + glm::vec2( 30, 30 ); }
		virtual glm::vec2 getMinCorner() const { return this->position - glm::vec2( 30, 30 ); }

		void setPulses( unsigned int pulses ) { this->pulses = pulses; }

	private:
		Net::PulseNode * node = nullptr;
		unsigned int pulses = 0;
		glm::vec2 position = glm::vec2(0,0);
	};
}

#endif
