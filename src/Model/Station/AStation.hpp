#ifndef _MODEL_STATION_ASTATION_INCLUDED_
#define _MODEL_STATION_ASTATION_INCLUDED_


#include <Model/ACircle2D.hpp>
#include <Model/AUpdateable.hpp>
#include <Model/EventSystem.hpp>


namespace Model
{
	class EventHandler;

	namespace Station
	{
		class AStation : public AUpdateable, public AAutoEventSource
		{
		public:
			AStation( EventHandler * eventHandler = nullptr );
			virtual ~AStation();

			virtual glm::vec2 getPosition() const { return this->position; }
			virtual void setPosition( const glm::vec2 & position ) { this->position = position; }

			virtual float getRadius() const = 0;

		private:
			glm::vec2 position = glm::vec2(0,0);
		};
	}
}


#endif
