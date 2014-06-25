#include <View/Renderer/SFML/SolarPlantRenderer.hpp>
#include <View/Renderer/SFML/RenderContext.hpp>
#include <View/Renderer/RenderFactory.hpp>

#include <vector>

#include <SFML/Graphics.hpp>


using namespace View::Renderer::SFML;


RENDERFACTORY_REGISTER_UNORDEREDRENDERER( View::Renderer::SFML::RenderContext, Model::Station::SolarPlant, SolarPlantRenderer )


void SolarPlantRenderer::render() const
{
	sf::CircleShape circle( 10.0f );
	circle.setOrigin( 10.0f, 10.0f );
	circle.setOutlineColor( sf::Color::White );
	circle.setOutlineThickness( 2.0f );

	for( const Model::Station::SolarPlant * m : this->getModels() )
	{
		circle.setPosition( m->getPosition().x, m->getPosition().y );

		if( m->isPulseAvailable() )
			circle.setFillColor( sf::Color( 255, 255, 0 ) );
		else
			circle.setFillColor( sf::Color( 64, 64, 0 ) );

		this->context.getRenderWindow()->draw( circle );
	}
}
