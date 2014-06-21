#ifndef _VIEW_RENDERER_SDL2_SOLARPLANTRENDERER_INCLUDED_
#define _VIEW_RENDERER_SDL2_SOLARPLANTRENDERER_INCLUDED_


#include "../AUnorderedRenderer.hpp"
#include "../../../Model/EventSystem.hpp"
#include "../../../Model/Station/SolarPlant.hpp"


namespace View
{
	namespace Renderer
	{
		namespace SDL2
		{
			class RenderContext;
			class SolarPlantRenderer :
				public AUnorderedRenderer< Model::SolarPlant >,
				public Model::AAutoEventListener< Model::SolarPlant::NewEvent >,
				public Model::AAutoEventListener< Model::SolarPlant::DeleteEvent >
			{
			public:
				SolarPlantRenderer( RenderContext & context ) : context(context) {}
				virtual ~SolarPlantRenderer() {}

				virtual void draw() const override;

				virtual void onEvent( const Model::SolarPlant::NewEvent & event )
					{ this->addModel( event.solarPlant ); }
				virtual void onEvent( const Model::SolarPlant::DeleteEvent & event )
					{ this->removeModel( event.solarPlant ); };

			private:
				RenderContext & context;
			};
		}
	}
}


#endif
