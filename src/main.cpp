#include <iostream>
#include <typeinfo>
#include <set>

#include <glm/vec2.hpp>
#include <glm/geometric.hpp>

#include <SDL2/SDL.h>
//#include <SFML/Graphics.hpp>

#include "Model/Updater.hpp"
#include "Model/IntervalStepUpdater.hpp"
#include "Model/Station/SolarPlant.hpp"
#include "Model/Station/Phaser.hpp"
#include "Model/Station/Hub.hpp"
#include "Model/Net/PulseDistributor.hpp"
#include "Model/Net/PulseNode.hpp"
/*
#include "View/SFML/SolarPlantRenderer.hpp"
#include "View/SFML/PhaserRenderer.hpp"
#include "View/SFML/PulseLinkRenderer.hpp"
*/

#include "View/SDL2/SolarPlantRenderer.hpp"
#include "View/SDL2/PhaserRenderer.hpp"
#include "View/SDL2/PulseLinkRenderer.hpp"


enum MouseMode
{
	SOLARPLANT,
	PHASER,
	HUB,
	LINK,
	UNLINK
};

MouseMode mouseMode = SOLARPLANT;

Model::Updater * updater;
Model::IntervalStepUpdater * intervalStepUpdater;
Model::Net::PulseDistributor * pulseDistributor;
/*
View::SFML::SolarPlantRenderer * solarPlantRenderer;
View::SFML::PhaserRenderer * phaserRenderer;
View::SFML::PulseLinkRenderer * pulseLinkRenderer;
*/
View::SDL2::SolarPlantRenderer * solarPlantRenderer;
View::SDL2::PhaserRenderer * phaserRenderer;
View::SDL2::PulseLinkRenderer * pulseLinkRenderer;

std::set< Model::SolarPlant * > solarPlants;
std::set< Model::Phaser * > phasers;
std::set< Model::Hub * > hubs;
std::set< Model::Net::PulseLink * > links;


template< typename T >
static T * getAt( const glm::vec2 & pos )
{
	for( auto i : solarPlants )
	{
		if( pos.x > i->getMinCorner().x
		 && pos.x < i->getMaxCorner().x
		 && pos.y > i->getMinCorner().y
		 && pos.y < i->getMaxCorner().y
		)
			return i;
	}
	for( auto i : phasers )
	{
		if( pos.x > i->getMinCorner().x
		 && pos.x < i->getMaxCorner().x
		 && pos.y > i->getMinCorner().y
		 && pos.y < i->getMaxCorner().y
		)
			return i;
	}
/*
	for( auto i : hubs )
	{
		if( pos.x > i->getMinCorner().x
		 && pos.x < i->getMaxCorner().x
		 && pos.y > i->getMinCorner().y
		 && pos.y < i->getMaxCorner().y
		)
			return i;
	}
*/
	return nullptr;
}


static void click( const glm::vec2 & pos )
{
	Model::ABoundingBox2D * obj = getAt<Model::ABoundingBox2D>( pos );
	if( obj )
	{
		if( typeid( *obj ) == typeid( Model::SolarPlant ) )
			static_cast< Model::SolarPlant * >( obj )->setPulses( 10 );
		else if( typeid( *obj ) == typeid( Model::Phaser ) )
			static_cast< Model::Phaser * >( obj )->setPulses( 0 );
		return;
	}
	switch( mouseMode )
	{
	case SOLARPLANT:
	{
		Model::SolarPlant * m = new Model::SolarPlant;
		m->setPosition( pos );
		solarPlants.insert( m );
		updater->addUpdateable( m );
		solarPlantRenderer->addModel( m );
		pulseDistributor->addProvider( m );
		break;
	}
	case PHASER:
	{
		Model::Phaser * m = new Model::Phaser;
		m->setPosition( pos );
		phasers.insert( m );
		updater->addUpdateable( m );
		phaserRenderer->addModel( m );
		pulseDistributor->addConsumer( m );
		break;
	}
	default:
		break;
	}
}


static Model::APositionable2D * draggedObject = nullptr;
static Model::Net::APulseNodeActor * linkSource = nullptr;
static Model::Net::APulseNodeActor * linkSink = nullptr;


static void dragStart( const glm::vec2 & from )
{
	switch( mouseMode )
	{
		case SOLARPLANT:
		case PHASER:
		case HUB:
			if( !draggedObject )
				draggedObject = getAt<Model::APositionable2D>( from );
			break;
		case LINK:
		case UNLINK:
			linkSource = getAt<Model::Net::APulseNodeActor>( from );
			break;
	}
}


static void drag( const glm::vec2 & to )
{
	switch( mouseMode )
	{
		case SOLARPLANT:
		case PHASER:
		case HUB:
			if( draggedObject )
			{
				draggedObject->setPosition( to );
			}
			break;
		default:
			break;
	}
}


static void dragStop( const glm::vec2 & to )
{
	switch( mouseMode )
	{
		case SOLARPLANT:
		case PHASER:
		case HUB:
			if( draggedObject )
			{
				draggedObject->setPosition( to );
				draggedObject = nullptr;
			}
			break;
		case LINK:
			{
				linkSink = getAt<Model::Net::APulseNodeActor>( to );
				if( !linkSource || !linkSink )
					return;
				Model::Net::PulseLink * link = new Model::Net::PulseLink;
				if( Model::Net::PulseNode::setLink( linkSource->getNode(), linkSink->getNode(), link ) )
				{
					pulseLinkRenderer->addModel( link );
					links.insert( link );
				}
			}
			break;
		case UNLINK:
			{
				linkSink = getAt<Model::Net::APulseNodeActor>( to );
				if( !linkSource || !linkSink )
					return;
				Model::Net::PulseLink * link = const_cast< Model::Net::PulseLink * >( linkSource->getNode()->getOutLink( linkSink->getNode() ) );
				if( link )
				{
					if( Model::Net::PulseNode::setLink( linkSource->getNode(), linkSink->getNode(), nullptr ) )
					{
						pulseLinkRenderer->removeModel( link );
						links.erase( link );
					}
				}
			}
			break;
	}
}


int main( int argc, char ** argv )
{
	/*
	sf::RenderWindow window( sf::VideoMode(800, 600), "LzIS" );
	window.setVerticalSyncEnabled(true);
	*/


	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER );
	SDL_Window * window = SDL_CreateWindow(
		"LzIS",                 // window title
		SDL_WINDOWPOS_CENTERED, // the x position of the window
		SDL_WINDOWPOS_CENTERED, // the y position of the window
		800, 600,               // window width and height
		0                       // flags
	);
	if( !window )
	{
		std::cerr << "Could not create SDL2 window: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Renderer * renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_PRESENTVSYNC );
	if( !renderer )
	{
		std::cerr << "Could not create SDL2 renderer: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_RendererInfo info;
	if( SDL_GetRendererInfo( renderer, &info ) )
	{
		std::cerr << "Unable to retrieve SDL2 renderer information: " << SDL_GetError() << std::endl;
		return false;
	}
	std::cerr << "SDL2 renderer name: " << info.name << std::endl;


	pulseDistributor = new Model::Net::PulseDistributor;

	intervalStepUpdater = new Model::IntervalStepUpdater;
	intervalStepUpdater->setInterval( 0.2 );
	intervalStepUpdater->addStepUpdateable( pulseDistributor );

	updater = new Model::Updater;
	updater->addUpdateable( intervalStepUpdater );
/*
	solarPlantRenderer = new View::SFML::SolarPlantRenderer( window );
	phaserRenderer = new View::SFML::PhaserRenderer( window );
	pulseLinkRenderer = new View::SFML::PulseLinkRenderer( window );
*/

	solarPlantRenderer = new View::SDL2::SolarPlantRenderer( renderer );
	phaserRenderer = new View::SDL2::PhaserRenderer( renderer );
	pulseLinkRenderer = new View::SDL2::PulseLinkRenderer( renderer );

/*
	sf::Clock clock;
	while( window.isOpen() )
	{
		sf::Time elapsed = clock.restart();

		sf::Event event;
		while( window.pollEvent(event) )
		{
			if( event.type == sf::Event::Closed )
				window.close();
			static glm::vec2 lastMousePos = glm::vec2(0,0);
			static bool dragging = false;
			switch( event.type )
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch( event.key.code )
					{
					case sf::Keyboard::Num1:
						mouseMode = SOLARPLANT;
						break;
					case sf::Keyboard::Num2:
						mouseMode = PHASER;
						break;
					case sf::Keyboard::Num3:
						mouseMode = HUB;
						break;
					case sf::Keyboard::Num4:
						mouseMode = LINK;
						break;
					case sf::Keyboard::Num5:
						mouseMode = UNLINK;
						break;
					default:
						break;
					}
				case sf::Event::MouseButtonPressed:
					switch( event.mouseButton.button )
					{
					case sf::Mouse::Left:
						lastMousePos = glm::vec2( event.mouseButton.x, event.mouseButton.y );
						break;
					default:
						break;
					}
					break;
				case sf::Event::MouseMoved:
					{
						if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
						{
							glm::vec2 currentMousePos( event.mouseMove.x, event.mouseMove.y );
							if( !dragging )
							{
								if( glm::distance( currentMousePos, lastMousePos ) >= 5.0f )
								{
									dragStart( currentMousePos );
									dragging = true;
								}
							}
							else
								drag( currentMousePos );
						}
					}
					break;
				case sf::Event::MouseButtonReleased:
					switch( event.mouseButton.button )
					{
					case sf::Mouse::Left:
						{
							glm::vec2 currentMousePos( event.mouseButton.x, event.mouseButton.y );
							if( dragging )
							{
								dragStop( currentMousePos );
								dragging = false;
							}
							else
							{
								click( currentMousePos );
							}
						}
						break;
					default:
						break;
					}
					break;
				default:
					break;
			}
		}

		updater->update( elapsed.asSeconds() );

		window.clear( sf::Color::Black );

		pulseLinkRenderer->draw();
		solarPlantRenderer->draw();
		phaserRenderer->draw();

		window.display();
	}
	*/

	unsigned int lastTime = 0, currentTime;
	bool running = true;
	while( running )
	{
		currentTime = SDL_GetTicks();
		float delta = (currentTime - lastTime) / 1000.0;
		lastTime = currentTime;

		SDL_Event event;
		while( SDL_PollEvent(&event) )
		{
			static glm::vec2 lastMousePos = glm::vec2(0,0);
			static bool dragging = false;
			switch( event.type )
			{
				case SDL_QUIT:
				{
					running = false;
					break;
				}
				case SDL_KEYDOWN:
				{
					SDL_Keycode key = event.key.keysym.sym;
					switch( key )
					{
					case SDLK_1:
						mouseMode = SOLARPLANT;
						break;
					case SDLK_2:
						mouseMode = PHASER;
						break;
					case SDLK_3:
						mouseMode = HUB;
						break;
					case SDLK_4:
						mouseMode = LINK;
						break;
					case SDLK_5:
						mouseMode = UNLINK;
						break;
					default:
						break;
					}
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
					switch( event.button.button )
					{
					case SDL_BUTTON_LEFT:
						lastMousePos = glm::vec2( event.button.x, event.button.y );
						break;
					default:
						break;
					}
					break;
				case SDL_MOUSEMOTION:
					{
						if( event.motion.state & SDL_BUTTON_LMASK )
						{
							glm::vec2 currentMousePos( event.motion.x, event.motion.y );
							if( !dragging )
							{
								if( glm::distance( currentMousePos, lastMousePos ) >= 5.0f )
								{
									dragStart( currentMousePos );
									dragging = true;
								}
							}
							else
								drag( currentMousePos );
						}
					}
					break;
				case SDL_MOUSEBUTTONUP:
					switch( event.button.button )
					{
					case SDL_BUTTON_LEFT:
						{
							glm::vec2 currentMousePos( event.button.x, event.button.y );
							if( dragging )
							{
								dragStop( currentMousePos );
								dragging = false;
							}
							else
							{
								click( currentMousePos );
							}
						}
						break;
					default:
						break;
					}
					break;
				default:
					break;
			}
		}

		updater->update( delta );

		SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
		SDL_RenderClear( renderer );

		pulseLinkRenderer->draw();
		solarPlantRenderer->draw();
		phaserRenderer->draw();

		SDL_RenderPresent( renderer );
	}
}
