#ifndef _VIEW_RENDERER_GLES2_PHASERRENDERER_INCLUDED_
#define _VIEW_RENDERER_GLES2_PHASERRENDERER_INCLUDED_


#include "../AUnorderedRenderer.hpp"
#include "../../../Model/Station/Phaser.hpp"


namespace View
{
	namespace Renderer
	{
		namespace GLES2
		{
			class PhaserRenderer : public AUnorderedBatchRenderer< Model::Phaser >
			{
			public:
				PhaserRenderer() {}
				virtual ~PhaserRenderer() {}
				virtual void draw() const override;
			};
		}
	}
}


#endif
