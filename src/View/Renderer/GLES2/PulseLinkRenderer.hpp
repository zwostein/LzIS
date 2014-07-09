#ifndef _VIEW_RENDERER_GLES2_PULSELINKRENDERER_INCLUDED_
#define _VIEW_RENDERER_GLES2_PULSELINKRENDERER_INCLUDED_


#include "../AUnorderedRenderer.hpp"
#include "../../../Model/Net/PulseLink.hpp"


namespace View
{
	namespace Renderer
	{
		namespace GLES2
		{
			class PulseLinkRenderer : public AUnorderedRenderer< Model::Net::PulseLink >
			{
			public:
				PulseLinkRenderer() {}
				virtual ~PulseLinkRenderer() {}
				virtual void draw() const override;
			};
		}
	}
}


#endif
