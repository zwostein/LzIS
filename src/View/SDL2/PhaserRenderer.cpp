#include "PhaserRenderer.hpp"

#include <vector>

using namespace View::SDL2;


void PhaserRenderer::draw() const
{
	std::vector< SDL_Rect > bright;
	std::vector< SDL_Rect > dark;

	for( const Model::Phaser * m : this->getModels() )
	{
		SDL_Rect r;
		r.x = m->getPosition().x - 10.0f;
		r.y = m->getPosition().y - 10.0f;
		r.w = 20;
		r.h = 20;

		if( m->isPulseNeeded() )
			dark.push_back( r );
		else
			bright.push_back( r );
	}

	SDL_SetRenderDrawColor( this->renderer, 0, 255, 255, 255 );
	SDL_RenderFillRects( this->renderer, bright.data(), bright.size() );

	SDL_SetRenderDrawColor( this->renderer, 0, 64, 64, 255 );
	SDL_RenderFillRects( this->renderer, dark.data(), dark.size() );

	SDL_SetRenderDrawColor( this->renderer, 255, 255, 255, 255 );
	SDL_RenderDrawRects( this->renderer, bright.data(), bright.size() );
	SDL_RenderDrawRects( this->renderer, dark.data(), dark.size() );
}
