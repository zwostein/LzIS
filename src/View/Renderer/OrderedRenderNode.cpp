#include <View/Renderer/OrderedRenderNode.hpp>


using namespace View::Renderer;


bool OrderedRenderNode::removeRenderable( const ARenderable * renderable )
{
	auto it = renderablesAsKeys.find( renderable );
	if( it == renderablesAsKeys.end() )
		return false; // not tracked
	int order = (*it).second;
	renderablesAsKeys.erase( it );

	auto itSameOrderRange = renderablesAsValues.equal_range( order );
	for( auto itSameOrder = itSameOrderRange.first; itSameOrder != itSameOrderRange.second; ++itSameOrder )
	{
		if( itSameOrder->second == renderable )
		{
			renderablesAsValues.erase( itSameOrder );
			break;
		}
	}
	return true;
}


bool OrderedRenderNode::addRenderable( const ARenderable * renderable, int order )
{
	auto it = renderablesAsKeys.find( renderable );
	if( it != renderablesAsKeys.end() )
		return false; // already tracked
	renderablesAsKeys[renderable] = order;
	renderablesAsValues.insert( std::pair< int, const ARenderable * >( order, renderable ) );
	return true;
}


void OrderedRenderNode::render() const
{
	for( const auto d : this->getRenderables() )
	{
		d.second->render();
	}
}
