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
				public AAutoEventListener< Model::Station::SolarPlant::NewEvent >,
				public AAutoEventListener< Model::Station::SolarPlant::DeleteEvent >
			{
			public:
				SolarPlantRenderer( RenderContext & context ) :
					AAutoEventListener< Model::Station::SolarPlant::NewEvent >( context.getEventHandler() ),
					AAutoEventListener< Model::Station::SolarPlant::DeleteEvent >( context.getEventHandler() ),
					context(context)
					{}
				virtual ~SolarPlantRenderer() {}

				virtual void render() const override;

				virtual void onEvent( const Model::Station::SolarPlant::NewEvent & event ) override
					{ this->addModel( event.getStation() ); }
				virtual void onEvent( const Model::Station::SolarPlant::DeleteEvent & event ) override
					{ this->removeModel( event.getStation() ); }

			private:
				RenderContext & context;
			};
		}
	}
}


#endif
