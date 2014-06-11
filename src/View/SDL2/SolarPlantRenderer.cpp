#include "SolarPlantRenderer.hpp"

#include<vector>


using namespace View::SDL2;


void SolarPlantRenderer::draw() const
{
	std::vector< SDL_Rect > bright;
	std::vector< SDL_Rect > dark;

	for( const Model::SolarPlant * m : this->getModels() )
	{
		SDL_Rect r;
		r.x = m->getPosition().x - 10.0f;
		r.y = m->getPosition().y - 10.0f;
		r.w = 20;
		r.h = 20;

		if( m->isPulseAvailable() )
			bright.push_back( r );
		else
			dark.push_back( r );
	}

	SDL_SetRenderDrawColor( this->renderer, 255, 255, 0, 255 );
	SDL_RenderFillRects( this->renderer, bright.data(), bright.size() );

	SDL_SetRenderDrawColor( this->renderer, 64, 64, 0, 255 );
	SDL_RenderFillRects( this->renderer, dark.data(), dark.size() );

	SDL_SetRenderDrawColor( this->renderer, 255, 255, 255, 255 );
	SDL_RenderDrawRects( this->renderer, bright.data(), bright.size() );
	SDL_RenderDrawRects( this->renderer, dark.data(), dark.size() );
}