#include "SolarPlantRenderer.hpp"


using namespace View::SFML;


void SolarPlantRenderer::draw() const
{
	sf::CircleShape circle( 10.0f );
	circle.setOrigin( 10.0f, 10.0f );
	circle.setOutlineColor( sf::Color::White );
	circle.setOutlineThickness( 2.0f );

	for( const Model::SolarPlant * m : this->getModels() )
	{
		circle.setPosition( m->getPosition().x, m->getPosition().y );

		if( m->isPulseAvailable() )
			circle.setFillColor( sf::Color( 255, 255, 0 ) );
		else
			circle.setFillColor( sf::Color( 64, 64, 0 ) );

		this->window.draw( circle );
	}
}
