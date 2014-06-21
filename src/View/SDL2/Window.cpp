#include "Window.hpp"
#include "../Renderer/SDL2/RenderContext.hpp"

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


Window::Window( const std::string & name ) : pImpl( new Impl )
{
	if( !SDL_WasInit( SDL_INIT_VIDEO ) )
		SDL_InitSubSystem( SDL_INIT_VIDEO );

	if( !SDL_WasInit( SDL_INIT_EVENTS ) )
		SDL_InitSubSystem( SDL_INIT_EVENTS );

	if( !SDL_WasInit( SDL_INIT_TIMER ) )
		SDL_InitSubSystem( SDL_INIT_TIMER );

	this->pImpl->window = SDL_CreateWindow(
		name.c_str(),           // window title
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

	this->context = new Renderer::SDL2::RenderContext( this->pImpl->renderer );
}


Window::~Window()
{
	delete static_cast< Renderer::SDL2::RenderContext * >(this->context);
	SDL_DestroyRenderer( this->pImpl->renderer );
	SDL_DestroyWindow( this->pImpl->window );
}


void Window::draw() const
{
	SDL_SetRenderDrawColor( static_cast< Renderer::SDL2::RenderContext * >(this->context)->getRenderer(), 0, 0, 0, 0 );
	SDL_RenderClear( static_cast< Renderer::SDL2::RenderContext * >(this->context)->getRenderer() );

	if( this->drawable )
		this->drawable->draw();

	SDL_RenderPresent( static_cast< Renderer::SDL2::RenderContext * >(this->context)->getRenderer() );
}
