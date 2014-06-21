#ifndef _VIEW_RENDERER_SFML_SOLARPLANTRENDERER_INCLUDED_
#define _VIEW_RENDERER_SFML_SOLARPLANTRENDERER_INCLUDED_


#include "../AUnorderedRenderer.hpp"
#include "../../../Model/Station/SolarPlant.hpp"


namespace View
{
	namespace Renderer
	{
		namespace SFML
		{
			class RenderContext;
			class SolarPlantRenderer : public AUnorderedRenderer< Model::SolarPlant >
			{
			public:
				SolarPlantRenderer( RenderContext & context ) : context(context) {}
				virtual ~SolarPlantRenderer() {}
				virtual void draw() const override;
			private:
				RenderContext & context;
			};
		}
	}
}


#endif
