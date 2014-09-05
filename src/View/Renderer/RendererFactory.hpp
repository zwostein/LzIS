#ifndef _VIEW_RENDERER_RENDERERFACTORY_INCLUDED_
#define _VIEW_RENDERER_RENDERERFACTORY_INCLUDED_


#include <View/Renderer/ARenderable.hpp>
#include <View/Renderer/BatchRenderNode.hpp>
#include <View/RenderContext/ARenderContext.hpp>

#include <map>
#include <unordered_map>
#include <typeindex>
#include <functional>


#define RENDERERFACTORY_REGISTER_RENDERER( ContextClass, RendererClass, level ) \
	static bool registeredAtRendererFactory = View::Renderer::RendererFactory::registerRenderer( \
		typeid(ContextClass), \
		[](View::RenderContext::ARenderContext & context) -> View::Renderer::ARenderable * \
			{ return new RendererClass( dynamic_cast<ContextClass&>(context) ); }, \
		level \
	); \


namespace View
{
	namespace Renderer
	{
		class RendererFactory
		{
		public:
			RendererFactory() = delete;
			RendererFactory( RendererFactory & ) = delete;
			RendererFactory & operator=( const RendererFactory & ) = delete;

			typedef std::type_index ContextType;
			typedef std::function< ARenderable * ( View::RenderContext::ARenderContext & ) > CreatorFunction;
			typedef std::pair< int, CreatorFunction > CreatorFunctionPair;
			typedef std::multimap< int, CreatorFunction > CreatorFunctionSet;
			typedef std::unordered_map< ContextType, CreatorFunctionSet > CreatorMap;

			static BatchRenderNode * newRenderer( RenderContext::ARenderContext & context );
			static void deleteRenderer( BatchRenderNode * renderer );
			static bool registerRenderer( ContextType contextType, CreatorFunction creator, int level );

		private:
			static CreatorMap creatorMap;
		};
	}
}


#endif
