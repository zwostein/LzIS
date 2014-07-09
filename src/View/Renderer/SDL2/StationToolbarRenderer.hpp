#ifndef _VIEW_RENDERER_SDL2_STATIONTOOLBARRENDERER_INCLUDED_
#define _VIEW_RENDERER_SDL2_STATIONTOOLBARRENDERER_INCLUDED_


#include <View/Renderer/SDL2/RenderContext.hpp>
#include <View/Renderer/AUnorderedBatchRenderer.hpp>
#include <Controller/StationToolbar.hpp>


struct SDL_Texture;


namespace View
{
	namespace Renderer
	{
		namespace SDL2
		{
			class StationToolbarRenderer :
				public AUnorderedBatchRenderer< Controller::StationToolbar >
			{
			public:
				StationToolbarRenderer( RenderContext & context );
				virtual ~StationToolbarRenderer();

				virtual void render() const override;

			private:
				RenderContext & context;
				SDL_Texture * texture;
			};
		}
	}
}


#endif
