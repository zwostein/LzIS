#ifndef _VIEW_RENDERER_SDL2_RENDERCONTEXT_INCLUDED_
#define _VIEW_RENDERER_SDL2_RENDERCONTEXT_INCLUDED_


#include "../ARenderContext.hpp"


struct SDL_Renderer;


namespace View
{
	namespace Renderer
	{
		namespace SDL2
		{
			class RenderContext : public ARenderContext
			{
			public:
				RenderContext( SDL_Renderer * renderer ) : renderer(renderer) {}
				virtual ~RenderContext() {}
				virtual std::string getName() const override { return "SDL2"; }
				SDL_Renderer * getRenderer() const { return this->renderer; }
			private:
				SDL_Renderer * renderer;
			};
		}
	}
}


#endif
