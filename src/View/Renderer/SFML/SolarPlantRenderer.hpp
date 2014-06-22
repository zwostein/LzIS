#ifndef _VIEW_RENDERER_SFML_SOLARPLANTRENDERER_INCLUDED_
#define _VIEW_RENDERER_SFML_SOLARPLANTRENDERER_INCLUDED_


#include <View/Renderer/SFML/RenderContext.hpp>
#include <View/Renderer/AUnorderedRenderer.hpp>
#include <Model/Station/SolarPlant.hpp>


namespace View
{
	namespace Renderer
	{
		namespace SFML
		{
			class SolarPlantRenderer :
				public AUnorderedRenderer< Model::Station::SolarPlant >,
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

				virtual void draw() const override;

				virtual void onEvent( const Model::Station::SolarPlant::NewEvent & event )
					{ this->addModel( event.solarPlant ); }
				virtual void onEvent( const Model::Station::SolarPlant::DeleteEvent & event )
					{ this->removeModel( event.solarPlant ); }

			private:
				RenderContext & context;
			};
		}
	}
}


#endif
