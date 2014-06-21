#ifndef _VIEW_RENDERER_SDL2_PHASERRENDERER_INCLUDED_
#define _VIEW_RENDERER_SDL2_PHASERRENDERER_INCLUDED_


#include "../AUnorderedRenderer.hpp"
#include "../../../Model/Station/Phaser.hpp"


namespace View
{
	namespace Renderer
	{
		namespace SDL2
		{
			class RenderContext;
			class PhaserRenderer :
				public AUnorderedRenderer< Model::Phaser >,
				public Model::AAutoEventListener< Model::Phaser::NewEvent >,
				public Model::AAutoEventListener< Model::Phaser::DeleteEvent >
			{
			public:
				PhaserRenderer( RenderContext & context ) : context(context) {}
				virtual ~PhaserRenderer() {}

				virtual void draw() const override;

				virtual void onEvent( const Model::Phaser::NewEvent & event )
					{ this->addModel( event.phaser ); }
				virtual void onEvent( const Model::Phaser::DeleteEvent & event )
					{ this->removeModel( event.phaser ); };

			private:
				RenderContext & context;
			};
		}
	}
}


#endif
