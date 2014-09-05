#ifndef _VIEW_RENDERCONTEXT_SDL2_INCLUDED_
#define _VIEW_RENDERCONTEXT_SDL2_INCLUDED_


#include <View/RenderContext/ARenderContext.hpp>

#include <glm/mat3x3.hpp>


struct SDL_Window;
struct SDL_Renderer;


namespace View
{
	namespace RenderContext
	{
		class SDL2 : public ARenderContext
		{
		public:
			SDL2( EventHandler * eventHandler, SDL_Renderer * renderer, SDL_Window * window ) :
				ARenderContext(eventHandler),
				renderer(renderer),
				window(window)
			{}
			virtual ~SDL2() {}

			virtual std::string getName() const override { return "SDL2"; }

			SDL_Renderer * getRenderer() const { return this->renderer; }
			SDL_Window * getWindow() const { return this->window; }

			const glm::mat3x3 & getScreenTransform() const { return this->screenTransform; }
			void setScreenTransform( const glm::mat3x3 & transform ) { this->screenTransform = transform; }

		private:
			SDL_Renderer * renderer;
			SDL_Window * window;
			glm::mat3x3 screenTransform;
		};
	}
}


#endif
