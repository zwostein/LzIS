#ifndef _VIEW_SFML_SOLARPLANTRENDERER_INCLUDED_
#define _VIEW_SFML_SOLARPLANTRENDERER_INCLUDED_


#include <SFML/Graphics.hpp>

#include "../AUnorderedRenderer.hpp"
#include "../../Model/Station/SolarPlant.hpp"


namespace View
{
	namespace SFML
	{
		class SolarPlantRenderer : public AUnorderedRenderer< Model::SolarPlant >
		{
		public:
			SolarPlantRenderer( sf::RenderWindow & window ) : window(window) {}
			virtual ~SolarPlantRenderer() {}
			virtual void draw() const override;
		private:
			sf::RenderWindow & window;
		};
	}
}


#endif
