#ifndef _VIEW_RENDERER_SFML_PULSELINKRENDERER_INCLUDED_
#define _VIEW_RENDERER_SFML_PULSELINKRENDERER_INCLUDED_


#include "../AUnorderedRenderer.hpp"
#include "../../../Model/Net/PulseLink.hpp"


namespace View
{
	namespace Renderer
	{
		namespace SFML
		{
			class RenderContext;
			class PulseLinkRenderer : public AUnorderedRenderer< Model::Net::PulseLink >
			{
			public:
				PulseLinkRenderer( RenderContext & context ) : context(context) {}
				virtual ~PulseLinkRenderer() {}
				virtual void draw() const override;
			private:
				RenderContext & context;
			};
		}
	}
}


#endif
