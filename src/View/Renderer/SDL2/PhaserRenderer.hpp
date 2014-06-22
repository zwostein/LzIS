#ifndef _VIEW_RENDERER_SDL2_PHASERRENDERER_INCLUDED_
#define _VIEW_RENDERER_SDL2_PHASERRENDERER_INCLUDED_


#include <View/Renderer/SDL2/RenderContext.hpp>
#include <View/Renderer/AUnorderedRenderer.hpp>
#include <Model/Station/Phaser.hpp>


namespace View
{
	namespace Renderer
	{
		namespace SDL2
		{
			class PhaserRenderer :
				public AUnorderedRenderer< Model::Station::Phaser >,
				public Model::AAutoEventListener< Model::Station::Phaser::NewEvent >,
				public Model::AAutoEventListener< Model::Station::Phaser::DeleteEvent >
			{
			public:
				PhaserRenderer( RenderContext & context ) :
					Model::AAutoEventListener< Model::Station::Phaser::NewEvent >( context.getEventHandler() ),
					Model::AAutoEventListener< Model::Station::Phaser::DeleteEvent >( context.getEventHandler() ),
					context(context)
					{}
				virtual ~PhaserRenderer() {}

				virtual void draw() const override;

				virtual void onEvent( const Model::Station::Phaser::NewEvent & event )
					{ this->addModel( event.phaser ); }
				virtual void onEvent( const Model::Station::Phaser::DeleteEvent & event )
					{ this->removeModel( event.phaser ); }

			private:
				RenderContext & context;
			};
		}
	}
}


#endif
