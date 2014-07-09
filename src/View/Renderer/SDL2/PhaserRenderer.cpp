#include <View/Renderer/SDL2/PhaserRenderer.hpp>
#include <View/Renderer/SDL2/RenderContext.hpp>
#include <View/Renderer/RenderFactory.hpp>

#include <assert.h>

#include <vector>

#include <SDL_render.h>


using namespace View::Renderer::SDL2;


RENDERFACTORY_REGISTER( View::Renderer::SDL2::RenderContext, Model::Station::Phaser, PhaserRenderer )


void PhaserRenderer::render() const
{
	std::vector< SDL_Rect > bright;
	std::vector< SDL_Rect > dark;

	for( const Model::Station::Phaser * m : this->getModels() )
	{
		SDL_Rect r;
		r.x = m->getPosition().x - m->getRadius();
		r.y = m->getPosition().y - m->getRadius();
		r.w = 2.0f * m->getRadius();
		r.h = 2.0f * m->getRadius();

		if( m->isPulseNeeded() )
			dark.push_back( r );
		else
			bright.push_back( r );
	}

	SDL_SetRenderDrawColor( this->context.getRenderer(), 0, 255, 255, 255 );
	SDL_RenderFillRects( this->context.getRenderer(), bright.data(), bright.size() );

	SDL_SetRenderDrawColor( this->context.getRenderer(), 0, 64, 64, 255 );
	SDL_RenderFillRects( this->context.getRenderer(), dark.data(), dark.size() );

	SDL_SetRenderDrawColor( this->context.getRenderer(), 255, 255, 255, 255 );
	SDL_RenderDrawRects( this->context.getRenderer(), bright.data(), bright.size() );
	SDL_RenderDrawRects( this->context.getRenderer(), dark.data(), dark.size() );
}
