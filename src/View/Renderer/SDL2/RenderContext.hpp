#ifndef _VIEW_RENDERER_SDL2_RENDERCONTEXT_INCLUDED_
#define _VIEW_RENDERER_SDL2_RENDERCONTEXT_INCLUDED_


#include <View/Renderer/ARenderContext.hpp>


struct SDL_Window;
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
				RenderContext( EventHandler * eventHandler, SDL_Renderer * renderer, SDL_Window * window ) :
					ARenderContext(eventHandler),
					renderer(renderer),
					window(window)
				{}
				virtual ~RenderContext() {}

				virtual std::string getName() const override { return "SDL2"; }

				SDL_Renderer * getRenderer() const { return this->renderer; }
				SDL_Window * getWindow() const { return this->window; }

			private:
				SDL_Renderer * renderer;
				SDL_Window * window;
			};
		}
	}
}


#endif
