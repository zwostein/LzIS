#ifndef _VIEW_RENDERER_SDL2_PHASERRENDERER_INCLUDED_
#define _VIEW_RENDERER_SDL2_PHASERRENDERER_INCLUDED_


#include <View/RenderContext/SDL2.hpp>
#include <View/Renderer/ARenderable.hpp>

#include <Model/Station/Phaser.hpp>

#include <unordered_set>


namespace View
{
	namespace Renderer
	{
		namespace SDL2
		{
			class PhaserRenderer :
				public ARenderable,
				public AAutoEventListener< Model::Station::Phaser::NewEvent >,
				public AAutoEventListener< Model::Station::Phaser::DeleteEvent >
			{
			public:
				PhaserRenderer( RenderContext::SDL2 & context ) :
					AAutoEventListener< Model::Station::Phaser::NewEvent >( context.getEventHandler() ),
					AAutoEventListener< Model::Station::Phaser::DeleteEvent >( context.getEventHandler() ),
					context(context)
					{}
				virtual ~PhaserRenderer() {}

				virtual void render() const override;

				virtual void onEvent( const Model::Station::Phaser::NewEvent & event ) override
					{ this->models.insert( &event.getStation() ); }
				virtual void onEvent( const Model::Station::Phaser::DeleteEvent & event ) override
					{ this->models.erase( &event.getStation() ); }

			private:
				RenderContext::SDL2 & context;
				std::unordered_set< const Model::Station::Phaser * > models;
			};
		}
	}
}


#endif
