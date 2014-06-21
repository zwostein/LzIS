#include "PhaserRenderer.hpp"
#include "RenderContext.hpp"
#include "../RenderFactory.hpp"

#include <SFML/Graphics.hpp>


using namespace View::Renderer::SFML;


RENDERFACTORY_REGISTER_UNORDEREDRENDERER( View::Renderer::SFML::RenderContext, Model::Phaser, PhaserRenderer )


void PhaserRenderer::draw() const
{
	sf::CircleShape circle( 10.0f );
	circle.setOrigin( 10.0f, 10.0f );
	circle.setOutlineColor( sf::Color::White );
	circle.setOutlineThickness( 2.0f );

	for( const Model::Phaser * m : this->getModels() )
	{
		circle.setPosition( m->getPosition().x, m->getPosition().y );

		if( !m->isPulseNeeded() )
			circle.setFillColor( sf::Color( 0, 255, 255 ) );
		else
			circle.setFillColor( sf::Color( 0, 64, 64 ) );

		this->context.getRenderWindow()->draw( circle );
	}
}