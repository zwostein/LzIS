#include "PulseLinkRenderer.hpp"
#include "../../Model/Net/PulseNode.hpp"
#include <glm/geometric.hpp>


using namespace View::SDL2;


void PulseLinkRenderer::draw() const
{
	for( const Model::Net::PulseLink * m : this->getModels() )
	{
		if( !m->from || !m->to )
			continue;

		if( m->pulse )
			SDL_SetRenderDrawColor( this->renderer, 128, 0, 255, 255 );
		else
			SDL_SetRenderDrawColor( this->renderer, 64, 0, 255, 255 );

		SDL_RenderDrawLine( this->renderer,
		                    m->from->getPosition().x, m->from->getPosition().y,
		                    m->to->getPosition().x, m->to->getPosition().y );

		glm::vec2 lineDir = glm::normalize( m->to->getPosition() - m->from->getPosition() );
		glm::vec2 perpDir( lineDir.y, -lineDir.x );
		glm::vec2 arrowFrom = m->to->getPosition() - 12.0f*lineDir;
		glm::vec2 arrowTo = arrowFrom + 10.0f*perpDir - 15.0f*lineDir;

		SDL_RenderDrawLine( this->renderer,
		                    arrowFrom.x, arrowFrom.y,
		                    arrowTo.x, arrowTo.y );
	}
}
