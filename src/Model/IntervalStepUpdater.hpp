#ifndef _MODEL_INTERVALSTEPUPDATER_INCLUDED_
#define _MODEL_INTERVALSTEPUPDATER_INCLUDED_


#include "AUpdateable.hpp"
#include "AStepUpdater.hpp"

#include <unordered_set>
#include <vector>


namespace Model
{
	class IntervalStepUpdater : public AStepUpdater, public AUpdateable
	{
	public:
		virtual bool addStepUpdateable( AStepUpdateable * stepUpdateable ) override;
		virtual bool removeStepUpdateable( AStepUpdateable * stepUpdateable ) override;

		virtual void update( double delta ) override;

		void setInterval( double interval ) { this->interval = interval; }
		double getInterval() { return this->interval; }

	private:
		double elapsed = 0.0;
		double interval = 1.0f;
		std::vector< AStepUpdateable * >stepUpdateables;
	};
}


#endif
