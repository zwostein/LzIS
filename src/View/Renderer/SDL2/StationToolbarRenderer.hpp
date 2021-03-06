#ifndef _VIEW_RENDERER_SDL2_STATIONTOOLBARRENDERER_INCLUDED_
#define _VIEW_RENDERER_SDL2_STATIONTOOLBARRENDERER_INCLUDED_


#include <View/RenderContext/SDL2.hpp>
#include <View/Renderer/ARenderable.hpp>
#include <Controller/StationToolbar.hpp>

#include <unordered_set>
#include <iostream>


struct SDL_Texture;


namespace View
{
	namespace Renderer
	{
		namespace SDL2
		{
			class StationToolbarRenderer :
				public ARenderable,
				public AAutoEventListener< Controller::StationToolbar::NewEvent >,
				public AAutoEventListener< Controller::StationToolbar::DeleteEvent >
			{
			public:
				StationToolbarRenderer( RenderContext::SDL2 & context );
				virtual ~StationToolbarRenderer();

				virtual void render() const override;

				virtual void onEvent( const Controller::StationToolbar::NewEvent & event ) override
					{ this->models.insert( &event.getToolbar() ); }
				virtual void onEvent( const Controller::StationToolbar::DeleteEvent & event ) override
					{ this->models.erase( &event.getToolbar() ); }

			private:
				RenderContext::SDL2 & context;
				SDL_Texture * texture;
				std::unordered_set< const Controller::StationToolbar * > models;
			};
		}
	}
}


#endif
