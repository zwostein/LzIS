#include <View/Renderer/SFML/PhaserRenderer.hpp>
#include <View/Renderer/SFML/RenderContext.hpp>
#include <View/Renderer/RenderFactory.hpp>

#include <SFML/Graphics.hpp>


using namespace View::Renderer::SFML;


RENDERFACTORY_REGISTER( View::Renderer::SFML::RenderContext, Model::Station::Phaser, PhaserRenderer )


void PhaserRenderer::render() const
{
	sf::CircleShape circle( 10.0f );
	circle.setOrigin( 10.0f, 10.0f );
	circle.setOutlineColor( sf::Color::White );
	circle.setOutlineThickness( 2.0f );

	for( const Model::Station::Phaser * m : this->getModels() )
	{
		circle.setPosition( m->getPosition().x, m->getPosition().y );

		if( !m->isPulseNeeded() )
			circle.setFillColor( sf::Color( 0, 255, 255 ) );
		else
			circle.setFillColor( sf::Color( 0, 64, 64 ) );

		this->context.getRenderWindow()->draw( circle );
	}
}
