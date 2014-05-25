#ifndef _VIEW_SFML_PULSELINKRENDERER_INCLUDED_
#define _VIEW_SFML_PULSELINKRENDERER_INCLUDED_


#include <SFML/Graphics.hpp>

#include "../AUnorderedRenderer.hpp"
#include "../../Model/Net/PulseLink.hpp"


namespace View
{
	namespace SFML
	{
		class PulseLinkRenderer : public AUnorderedRenderer< Model::Net::PulseLink >
		{
		public:
			PulseLinkRenderer( sf::RenderWindow & window ) : window(window) {}
			virtual ~PulseLinkRenderer() {}
			virtual void draw() const override;
		private:
			sf::RenderWindow & window;
		};
	}
}


#endif
