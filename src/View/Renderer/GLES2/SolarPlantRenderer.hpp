#ifndef _VIEW_RENDERER_GLES2_SOLARPLANTRENDERER_INCLUDED_
#define _VIEW_RENDERER_GLES2_SOLARPLANTRENDERER_INCLUDED_


#include "../AUnorderedRenderer.hpp"
#include "../../../Model/Station/SolarPlant.hpp"


namespace View
{
	namespace Renderer
	{
		namespace GLES2
		{
			class SolarPlantRenderer : public AUnorderedBatchRenderer< Model::SolarPlant >
			{
			public:
				SolarPlantRenderer() {}
				virtual ~SolarPlantRenderer() {}
				virtual void draw() const override;
			};
		}
	}
}


#endif
