#ifndef _VIEW_RENDERER_SFML_PHASERRENDERER_INCLUDED_
#define _VIEW_RENDERER_SFML_PHASERRENDERER_INCLUDED_


#include "../AUnorderedRenderer.hpp"
#include "../../../Model/Station/Phaser.hpp"


namespace View
{
	namespace Renderer
	{
		namespace SFML
		{
			class RenderContext;
			class PhaserRenderer : public AUnorderedRenderer< Model::Phaser >
			{
			public:
				PhaserRenderer( RenderContext & context ) : context(context) {}
				virtual ~PhaserRenderer() {}
				virtual void draw() const override;
			private:
				RenderContext & context;
			};
		}
	}
}


#endif
