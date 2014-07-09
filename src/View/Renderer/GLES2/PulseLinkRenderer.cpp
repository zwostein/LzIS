#include "PulseLinkRenderer.hpp"
#include "../../../Model/Net/PulseNode.hpp"
#include <glm/geometric.hpp>


using namespace View::Renderer::GLES2;


void PulseLinkRenderer::draw() const
{
	for( const Model::Net::PulseLink * m : this->getModels() )
	{
	}
}
