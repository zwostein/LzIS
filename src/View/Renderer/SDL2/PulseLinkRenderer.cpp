#include <View/Renderer/SDL2/PulseLinkRenderer.hpp>
#include <View/RenderContext/SDL2.hpp>
#include <View/Renderer/RendererFactory.hpp>

#include <Model/Net/PulseLink.hpp>
#include <Model/Net/PulseNode.hpp>

#include <glm/geometric.hpp>

#include <SDL_render.h>


using namespace View::Renderer::SDL2;


RENDERERFACTORY_REGISTER_RENDERER( View::RenderContext::SDL2, PulseLinkRenderer, 0 )


void PulseLinkRenderer::render() const
{
	for( const Model::Net::PulseLink * m : this->models )
	{
		if( !m->from || !m->to )
			continue;

		if( m->pulse )
			SDL_SetRenderDrawColor( this->context.getRenderer(), 128, 0, 255, 255 );
		else
			SDL_SetRenderDrawColor( this->context.getRenderer(), 64, 0, 255, 255 );

		SDL_RenderDrawLine( this->context.getRenderer(),
		                    m->from->getPosition().x, m->from->getPosition().y,
		                    m->to->getPosition().x, m->to->getPosition().y );

		glm::vec2 lineDir = glm::normalize( m->to->getPosition() - m->from->getPosition() );
		glm::vec2 perpDir( lineDir.y, -lineDir.x );
		glm::vec2 arrowFrom = m->to->getPosition() - 12.0f*lineDir;
		glm::vec2 arrowTo = arrowFrom + 10.0f*perpDir - 15.0f*lineDir;

		SDL_RenderDrawLine( this->context.getRenderer(),
		                    arrowFrom.x, arrowFrom.y,
		                    arrowTo.x, arrowTo.y );
	}
}
