#include <View/Window/SDL2/Window.hpp>
#include <View/Renderer/SDL2/RenderContext.hpp>

#include <EventSystem.hpp>
#include <Controller/PointerEvent.hpp>

#include <iostream>
#include <stdexcept>

#include <SDL.h>


#define SDL2_ERROR( what ) \
	std::runtime_error( std::string(__PRETTY_FUNCTION__) + std::string(": ") + (what) + std::string(": ") + SDL_GetError() )


using namespace View::SDL2;


class Window::Impl
{
public:
	SDL_Window * window;
	SDL_Renderer * renderer;
};


Window::Window( const std::string & title, EventHandler * eventHandler ) : AWindow(eventHandler), pImpl( new Impl )
{
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER );
/*
	if( !SDL_WasInit( SDL_INIT_VIDEO ) )
		SDL_InitSubSystem( SDL_INIT_VIDEO );

	if( !SDL_WasInit( SDL_INIT_EVENTS ) )
		SDL_InitSubSystem( SDL_INIT_EVENTS );

	if( !SDL_WasInit( SDL_INIT_TIMER ) )
		SDL_InitSubSystem( SDL_INIT_TIMER );
*/
	this->pImpl->window = SDL_CreateWindow(
		title.c_str(),           // window title
		SDL_WINDOWPOS_CENTERED, // the x position of the window
		SDL_WINDOWPOS_CENTERED, // the y position of the window
		800, 600,               // window width and height
		SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE // flags
	);
	if( !this->pImpl->window )
		throw SDL2_ERROR( "Could not create window" );

	this->pImpl->renderer = SDL_CreateRenderer( this->pImpl->window, -1, SDL_RENDERER_PRESENTVSYNC );
	if( !this->pImpl->renderer )
		throw SDL2_ERROR( "Could not create renderer" );

	SDL_RendererInfo info;
	if( SDL_GetRendererInfo( this->pImpl->renderer, &info ) )
		throw SDL2_ERROR( "Could not get renderer information" );

	std::cerr << "SDL2 renderer name: " << info.name << std::endl;
	std::cerr << "SDL2 detected " << SDL_GetNumTouchDevices() << " touch devices" << std::endl;

	this->context = new Renderer::SDL2::RenderContext( eventHandler, this->pImpl->renderer, this->pImpl->window );

	SDL_SetRenderDrawColor( static_cast< Renderer::SDL2::RenderContext * >(this->context)->getRenderer(), 0, 0, 0, 0 );
	SDL_RenderClear( static_cast< Renderer::SDL2::RenderContext * >(this->context)->getRenderer() );
}


Window::~Window()
{
	delete static_cast< Renderer::SDL2::RenderContext * >(this->context);
	SDL_DestroyRenderer( this->pImpl->renderer );
	SDL_DestroyWindow( this->pImpl->window );
}


void Window::processEvents()
{
	SDL_Event sdlEvent;
	while( SDL_PollEvent(&sdlEvent) )
	{
		switch( sdlEvent.type )
		{
		case SDL_QUIT:
			{
				this->closeRequested = true;
				break;
			}
		case SDL_MOUSEBUTTONDOWN:
			{
				int w = 0, h = 0;
				SDL_GetWindowSize( this->pImpl->window, &w, &h );
				Controller::PointerDownEvent e;

				e.button = sdlEvent.button.button;

				e.position.x = static_cast< decltype(e.position.x) >( sdlEvent.button.x )
				                / static_cast< decltype( e.position.x ) >(w-1);
				e.position.y = static_cast< decltype(e.position.y) >( sdlEvent.button.y )
				                / static_cast< decltype( e.position.y ) >(h-1);

				this->dispatch( e );
				break;
			}
		case SDL_MOUSEBUTTONUP:
			{
				int w = 0, h = 0;
				SDL_GetWindowSize( this->pImpl->window, &w, &h );
				Controller::PointerUpEvent e;

				e.button = sdlEvent.button.button;

				e.position.x = static_cast< decltype(e.position.x) >( sdlEvent.button.x )
				                / static_cast< decltype( e.position.x ) >(w-1);
				e.position.y = static_cast< decltype(e.position.y) >( sdlEvent.button.y )
				                / static_cast< decltype( e.position.y ) >(h-1);

				this->dispatch( e );
				break;
			}
		case SDL_MOUSEMOTION:
			{
				int w = 0, h = 0;
				SDL_GetWindowSize( this->pImpl->window, &w, &h );
				Controller::PointerMotionEvent e;

				e.position.x = static_cast< decltype(e.position.x) >( sdlEvent.motion.x )
				                / static_cast< decltype( e.position.x ) >(w-1);
				e.position.y = static_cast< decltype(e.position.y) >( sdlEvent.motion.y )
				                / static_cast< decltype( e.position.y ) >(h-1);

				e.delta.x = static_cast< decltype(e.delta.x) >( sdlEvent.motion.xrel )
				                / static_cast< decltype( e.delta.x ) >(w-1);
				e.delta.y = static_cast< decltype(e.delta.y) >( sdlEvent.motion.yrel )
				                / static_cast< decltype( e.delta.y ) >(h-1);

				this->dispatch( e );
				break;
			}
		case SDL_FINGERDOWN:
			std::cerr << "FINGERDOWN:\tfingerID=" << sdlEvent.tfinger.fingerId
				<< " touchID=" << sdlEvent.tfinger.touchId
				<< " x=" << sdlEvent.tfinger.x << " y=" << sdlEvent.tfinger.x
				<< " pressure=" << sdlEvent.tfinger.pressure
				<< std::endl;
			break;
		case SDL_FINGERUP:
			std::cerr << "SDL_FINGERUP:\tfingerID=" << sdlEvent.tfinger.fingerId
				<< " touchID=" << sdlEvent.tfinger.touchId
				<< " x=" << sdlEvent.tfinger.x << " y=" << sdlEvent.tfinger.x
				<< " pressure=" << sdlEvent.tfinger.pressure
				<< std::endl;
			break;
		case SDL_FINGERMOTION:
			std::cerr << "SDL_FINGERMOTION:\tfingerID=" << sdlEvent.tfinger.fingerId
				<< " touchID=" << sdlEvent.tfinger.touchId
				<< " x=" << sdlEvent.tfinger.x << " y=" << sdlEvent.tfinger.x
				<< " pressure=" << sdlEvent.tfinger.pressure
				<< std::endl;
			break;
		default:
			break;
		}
	}
}


void Window::display()
{
	SDL_RenderPresent( static_cast< Renderer::SDL2::RenderContext * >(this->context)->getRenderer() );
	SDL_SetRenderDrawColor( static_cast< Renderer::SDL2::RenderContext * >(this->context)->getRenderer(), 0, 0, 0, 0 );
	SDL_RenderClear( static_cast< Renderer::SDL2::RenderContext * >(this->context)->getRenderer() );
}
