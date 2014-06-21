#ifndef _VIEW_RENDERER_SFML_RENDERCONTEXT_INCLUDED_
#define _VIEW_RENDERER_SFML_RENDERCONTEXT_INCLUDED_


#include "../ARenderContext.hpp"


namespace sf
{
	class RenderWindow;
}


namespace View
{
	namespace Renderer
	{
		namespace SFML
		{
			class RenderContext : public ARenderContext
			{
			public:
				RenderContext( sf::RenderWindow * renderWindow ) : renderWindow(renderWindow) {}
				virtual ~RenderContext() {}
				virtual std::string getName() const override { return "SFML"; }
				sf::RenderWindow * getRenderWindow() const { return this->renderWindow; }
			private:
				sf::RenderWindow * renderWindow;
			};
		}
	}
}


#endif
