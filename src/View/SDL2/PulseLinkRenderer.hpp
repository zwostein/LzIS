#ifndef _VIEW_SDL2_PULSELINKRENDERER_INCLUDED_
#define _VIEW_SDL2_PULSELINKRENDERER_INCLUDED_


#include <SDL2/SDL_render.h>

#include "../AUnorderedRenderer.hpp"
#include "../../Model/Net/PulseLink.hpp"


namespace View
{
	namespace SDL2
	{
		class PulseLinkRenderer : public AUnorderedRenderer< Model::Net::PulseLink >
		{
		public:
			PulseLinkRenderer( SDL_Renderer * renderer ) : renderer(renderer) {}
			virtual ~PulseLinkRenderer() {}
			virtual void draw() const override;
		private:
			SDL_Renderer * renderer;
		};
	}
}


#endif
