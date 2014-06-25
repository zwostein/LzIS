#ifndef _VIEW_RENDERER_SDL2_SOLARPLANTRENDERER_INCLUDED_
#define _VIEW_RENDERER_SDL2_SOLARPLANTRENDERER_INCLUDED_


#include <View/Renderer/SDL2/RenderContext.hpp>
#include <View/Renderer/AUnorderedBatchRenderer.hpp>
#include <Model/Station/SolarPlant.hpp>


namespace View
{
	namespace Renderer
	{
		namespace SDL2
		{
			class SolarPlantRenderer :
				public AUnorderedBatchRenderer< Model::Station::SolarPlant >,
				public Model::AAutoEventListener< Model::Station::SolarPlant::NewEvent >,
				public Model::AAutoEventListener< Model::Station::SolarPlant::DeleteEvent >
			{
			public:
				SolarPlantRenderer( RenderContext & context ) :
					Model::AAutoEventListener< Model::Station::SolarPlant::NewEvent >( context.getEventHandler() ),
					Model::AAutoEventListener< Model::Station::SolarPlant::DeleteEvent >( context.getEventHandler() ),
					context(context)
					{}
				virtual ~SolarPlantRenderer() {}

				virtual void render() const override;

				virtual void onEvent( const Model::Station::SolarPlant::NewEvent & event )
					{ this->addModel( event.getStation() ); }
				virtual void onEvent( const Model::Station::SolarPlant::DeleteEvent & event )
					{ this->removeModel( event.getStation() ); }

			private:
				RenderContext & context;
			};
		}
	}
}


#endif
