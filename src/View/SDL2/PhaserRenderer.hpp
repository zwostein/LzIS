#ifndef _VIEW_SDL2_PHASERRENDERER_INCLUDED_
#define _VIEW_SDL2_PHASERRENDERER_INCLUDED_


#include <SDL2/SDL_render.h>

#include "../AUnorderedRenderer.hpp"
#include "../../Model/Station/Phaser.hpp"


namespace View
{
	namespace SDL2
	{
		class PhaserRenderer : public AUnorderedRenderer< Model::Phaser >
		{
		public:
			PhaserRenderer( SDL_Renderer * renderer ) : renderer(renderer) {}
			virtual ~PhaserRenderer() {}
			virtual void draw() const override;
		private:
			SDL_Renderer * renderer;
		};
	}
}


#endif
