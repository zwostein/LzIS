#ifndef _VIEW_SFML_PHASERRENDERER_INCLUDED_
#define _VIEW_SFML_PHASERRENDERER_INCLUDED_


#include <SFML/Graphics.hpp>

#include "../AUnorderedRenderer.hpp"
#include "../../Model/Station/Phaser.hpp"


namespace View
{
	namespace SFML
	{
		class PhaserRenderer : public AUnorderedRenderer< Model::Phaser >
		{
		public:
			PhaserRenderer( sf::RenderWindow & window ) : window(window) {}
			virtual ~PhaserRenderer() {}
			virtual void draw() const override;
		private:
			sf::RenderWindow & window;
		};
	}
}


#endif
