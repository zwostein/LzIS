#include <View/Renderer/RendererFactory.hpp>


using namespace View::Renderer;

RendererFactory::CreatorMap RendererFactory::creatorMap;


BatchRenderNode * RendererFactory::newRenderer( RenderContext::ARenderContext & context )
{
	BatchRenderNode * renderer = new BatchRenderNode;
	auto it = creatorMap.find( typeid(context) );
	if( it == creatorMap.end() )
		return nullptr;
	for( auto creatorFunctionPair : (*it).second )
	{
		ARenderable * renderable = creatorFunctionPair.second( context );
		if( renderable )
			renderer->append( *renderable );
	}
	return renderer;
}


void RendererFactory::deleteRenderer( BatchRenderNode * renderer )
{
	for( auto renderable : *renderer )
		delete renderable;
	delete renderer;
}


bool RendererFactory::registerRenderer( ContextType contextType, CreatorFunction creator, int level )
{
	creatorMap[ contextType ].insert( CreatorFunctionPair(level,creator) );
	return true;
}
