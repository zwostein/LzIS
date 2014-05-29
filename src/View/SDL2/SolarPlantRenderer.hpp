#ifndef _VIEW_SDL2_SOLARPLANTRENDERER_INCLUDED_
#define _VIEW_SDL2_SOLARPLANTRENDERER_INCLUDED_


#include <SDL2/SDL_render.h>

#include "../AUnorderedRenderer.hpp"
#include "../../Model/Station/SolarPlant.hpp"


namespace View
{
	namespace SDL2
	{
		class SolarPlantRenderer : public AUnorderedRenderer< Model::SolarPlant >
		{
		public:
			SolarPlantRenderer( SDL_Renderer * renderer ) : renderer(renderer) {}
			virtual ~SolarPlantRenderer() {}
			virtual void draw() const override;
		private:
			SDL_Renderer * renderer;
		};
	}
}


#endif
