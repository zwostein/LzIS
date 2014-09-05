#include <View/Renderer/SDL2/SolarPlantRenderer.hpp>
#include <View/Renderer/RendererFactory.hpp>
#include <View/RenderContext/SDL2.hpp>

#include <vector>

#include <SDL_render.h>


using namespace View::Renderer::SDL2;


RENDERERFACTORY_REGISTER_RENDERER( View::RenderContext::SDL2, SolarPlantRenderer, 0 )


void SolarPlantRenderer::render() const
{
	std::vector< SDL_Rect > bright;
	std::vector< SDL_Rect > dark;

	for( const Model::Station::SolarPlant * m : this->models )
	{
		SDL_Rect r;
		r.x = m->getPosition().x - m->getRadius();
		r.y = m->getPosition().y - m->getRadius();
		r.w = 2.0f * m->getRadius();
		r.h = 2.0f * m->getRadius();

		if( m->isPulseAvailable() )
			bright.push_back( r );
		else
			dark.push_back( r );
	}

	SDL_SetRenderDrawColor( this->context.getRenderer(), 255, 255, 0, 255 );
	SDL_RenderFillRects( this->context.getRenderer(), bright.data(), bright.size() );

	SDL_SetRenderDrawColor( this->context.getRenderer(), 64, 64, 0, 255 );
	SDL_RenderFillRects( this->context.getRenderer(), dark.data(), dark.size() );

	SDL_SetRenderDrawColor( this->context.getRenderer(), 255, 255, 255, 255 );
	SDL_RenderDrawRects( this->context.getRenderer(), bright.data(), bright.size() );
	SDL_RenderDrawRects( this->context.getRenderer(), dark.data(), dark.size() );
}
