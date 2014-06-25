#ifndef _VIEW_RENDERER_RENDERFACTORY_INCLUDED_
#define _VIEW_RENDERER_RENDERFACTORY_INCLUDED_


#include <View/Renderer/ARenderable.hpp>
#include <View/Renderer/ARenderContext.hpp>

#include <unordered_map>
#include <typeindex>
#include <functional>


#define RENDERFACTORY_REGISTER_UNORDEREDRENDERER( contextType, modelType, rendererType ) \
	namespace { \
		static View::Renderer::ARenderable * createRenderer( View::Renderer::ARenderContext & context ) \
		{ \
			return new rendererType( dynamic_cast<contextType&>( context ) ); \
		} \
		static bool registered = View::Renderer::RenderFactory::registerRenderer<modelType>( \
			std::type_index(typeid(contextType)), \
			View::Renderer::RenderFactory::CreatorFunction( createRenderer ) \
		); \
	} \


namespace View
{
	namespace Renderer
	{
		class RenderFactory
		{
		public:
			typedef std::type_index RenderType;
			typedef std::type_index ModelType;

			struct Key
			{
				Key( RenderType renderType, ModelType modelType ) : renderType(renderType), modelType(modelType) {}
				RenderType renderType;
				ModelType modelType;
				bool operator<( const Key & other ) const
				{
					if( this->renderType < other.renderType )
						return true;
					else if( this->renderType > other.renderType )
						return false;
					return this->modelType < other.modelType;
				}
				bool operator==( const Key & other ) const
				{
					return this->renderType == other.renderType && this->modelType == other.modelType;
				}
				struct Hash
				{
					size_t operator()( const Key & key ) const
					{
						return key.renderType.hash_code() ^ ( key.modelType.hash_code() + 0x9e3779b9 );
					}
				};
			};

			typedef std::function< void*(ARenderContext&) > CreatorFunction;
			typedef std::unordered_map< Key, CreatorFunction, Key::Hash > RendererMap;

			static ARenderable * newRenderer( ModelType modelType, ARenderContext & context )
			{
				auto i = renderers.find( Key( typeid(context), modelType ) );
				if( i == renderers.end() )
					throw std::runtime_error( "No known renderer for \"" + std::string(modelType.name()) + "\" using \"" + std::string(typeid(context).name()) + "\"" );
				return static_cast< ARenderable * >( i->second( context ) );
			}

			template< typename TModel >
			static ARenderable * newRenderer( ARenderContext & context )
			{
				return newRenderer( typeid(TModel), context );
			}

			template< typename TModel >
			static bool registerRenderer( std::type_index contextType, CreatorFunction creator )
			{
				if( renderers.count( Key( contextType, std::type_index(typeid(TModel)) ) ) )
					return false;
				renderers[ Key( contextType, std::type_index(typeid(TModel)) ) ] = creator;
				return true;
			}

		private:
			static RendererMap renderers;
		};
	}
}


#endif
