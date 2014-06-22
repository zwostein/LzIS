#include <View/Renderer/SFML/PulseLinkRenderer.hpp>
#include <View/Renderer/SFML/RenderContext.hpp>
#include <View/Renderer/RenderFactory.hpp>
#include <Model/Net/PulseNode.hpp>

#include <glm/geometric.hpp>

#include <SFML/Graphics.hpp>


using namespace View::Renderer::SFML;


RENDERFACTORY_REGISTER_UNORDEREDRENDERER( View::Renderer::SFML::RenderContext, Model::Net::PulseLink, PulseLinkRenderer )


void PulseLinkRenderer::draw() const
{
	for( const Model::Net::PulseLink * m : this->getModels() )
	{
		if( !m->from || !m->to )
			continue;
		glm::vec2 from = m->from->getPosition();
		glm::vec2 to = m->to->getPosition();
		sf::Vertex line[2] =
		{
			sf::Vertex(sf::Vector2f( from.x, from.y ), m->pulse?sf::Color( 128, 0, 255 ):sf::Color( 128, 0, 255, 64 ) ),
			sf::Vertex(sf::Vector2f( to.x, to.y ), m->pulse?sf::Color( 64, 0, 255 ):sf::Color( 64, 0, 255, 64 ) )
		};
		this->context.getRenderWindow()->draw( line, 2, sf::Lines );
	}
}
