#ifndef _VIEW_RENDERER_SFML_PHASERRENDERER_INCLUDED_
#define _VIEW_RENDERER_SFML_PHASERRENDERER_INCLUDED_


#include <View/Renderer/SFML/RenderContext.hpp>
#include <View/Renderer/AUnorderedBatchRenderer.hpp>
#include <Model/Station/Phaser.hpp>


namespace View
{
	namespace Renderer
	{
		namespace SFML
		{
			class PhaserRenderer :
				public AUnorderedBatchRenderer< Model::Station::Phaser >,
				public AAutoEventListener< Model::Station::Phaser::NewEvent >,
				public AAutoEventListener< Model::Station::Phaser::DeleteEvent >
			{
			public:
				PhaserRenderer( RenderContext & context ) :
					AAutoEventListener< Model::Station::Phaser::NewEvent >( context.getEventHandler() ),
					AAutoEventListener< Model::Station::Phaser::DeleteEvent >( context.getEventHandler() ),
					context(context)
					{}
				virtual ~PhaserRenderer() {}

				virtual void render() const override;

				virtual void onEvent( const Model::Station::Phaser::NewEvent & event ) override
					{ this->addModel( event.getStation() ); }
				virtual void onEvent( const Model::Station::Phaser::DeleteEvent & event ) override
					{ this->removeModel( event.getStation() ); }

			private:
				RenderContext & context;
			};
		}
	}
}


#endif
