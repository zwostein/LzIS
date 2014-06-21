#include "SolarPlantRenderer.hpp"
#include "RenderContext.hpp"
#include "../RenderFactory.hpp"

#include <vector>

#include <SDL_render.h>


using namespace View::Renderer::SDL2;


RENDERFACTORY_REGISTER_UNORDEREDRENDERER( View::Renderer::SDL2::RenderContext, Model::SolarPlant, SolarPlantRenderer )


void SolarPlantRenderer::draw() const
{
	std::vector< SDL_Rect > bright;
	std::vector< SDL_Rect > dark;

	for( const Model::SolarPlant * m : this->getModels() )
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