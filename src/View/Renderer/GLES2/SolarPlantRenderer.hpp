#ifndef _VIEW_RENDERER_SDL2_SOLARPLANTRENDERER_INCLUDED_
#define _VIEW_RENDERER_SDL2_SOLARPLANTRENDERER_INCLUDED_


#include <View/RenderContext/SDL2.hpp>
#include <View/Renderer/ARenderable.hpp>

#include <Model/Station/SolarPlant.hpp>

#include <unordered_set>


namespace View
{
	namespace Renderer
	{
		namespace SDL2
		{
			class SolarPlantRenderer :
				public ARenderable,
				public AAutoEventListener< Model::Station::SolarPlant::NewEvent >,
				public AAutoEventListener< Model::Station::SolarPlant::DeleteEvent >
			{
			public:
				SolarPlantRenderer( RenderContext::SDL2 & context ) :
					AAutoEventListener< Model::Station::SolarPlant::NewEvent >( context.getEventHandler() ),
					AAutoEventListener< Model::Station::SolarPlant::DeleteEvent >( context.getEventHandler() ),
					context(context)
					{}
				virtual ~SolarPlantRenderer() {}

				virtual void render() const override;

				virtual void onEvent( const Model::Station::SolarPlant::NewEvent & event ) override
					{ this->models.insert( &event.getStation() ); }
				virtual void onEvent( const Model::Station::SolarPlant::DeleteEvent & event ) override
					{ this->models.erase( &event.getStation() ); }

			private:
				RenderContext::SDL2 & context;
				std::unordered_set< const Model::Station::SolarPlant * > models;
			};
		}
	}
}


#endif
