#ifndef _MODEL_INTERVALSTEPPER_INCLUDED_
#define _MODEL_INTERVALSTEPPER_INCLUDED_


#include <Model/AUpdateable.hpp>
#include <Model/AStepable.hpp>


namespace Model
{
	class IntervalStepper : public AUpdateable
	{
	private:
		double elapsed = 0.0;
		double interval = 1.0f;
		AStepable & stepable;

	public:
		IntervalStepper( AStepable & stepable ) : stepable(stepable) {}
		virtual ~IntervalStepper() {}

		virtual void update( double delta ) override
		{
			this->elapsed += delta;
			while( this->elapsed >= this->interval )
			{
				this->elapsed -= this->interval;
				this->stepable.step();
			}
		}

		void setInterval( double interval ) { this->interval = interval; }
		double getInterval() const { return this->interval; }
	};
}


#endif
