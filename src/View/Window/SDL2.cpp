#include <View/Window/SDL2.hpp>
#include <View/RenderContext/ARenderContext.hpp>
#include <View/RenderContext/SDL2.hpp>
#include <View/RenderContext/GLES2.hpp>

#include <EventSystem.hpp>
#include <Controller/PointerEvent.hpp>

#include <iostream>
#include <stdexcept>

#include <SDL.h>
#include <SDL_opengles2.h>


#define SDL2_ERROR( what ) \
	std::runtime_error( std::string(__PRETTY_FUNCTION__) + std::string(": ") + (what) + std::string(": ") + SDL_GetError() )


using namespace View;
using namespace View::Window;


class SDL2::Impl
{
public:
	SDL_Window * window = nullptr;
	SDL_GLContext glContext = nullptr;
	SDL_Renderer * sdlRenderer = nullptr;

	RenderContext::ARenderContext * initWindow( const std::string & title, unsigned int width, unsigned int height, Flags flags, Context context, EventHandler * eventHandler )
	{
		if( !SDL_WasInit( SDL_INIT_VIDEO ) )
			SDL_InitSubSystem( SDL_INIT_VIDEO );

		if( !SDL_WasInit( SDL_INIT_EVENTS ) )
			SDL_InitSubSystem( SDL_INIT_EVENTS );

		Uint32 sdl2WindowFlags = 0;
		if( flags & Flags::FullScreen )  sdl2WindowFlags |= SDL_WINDOW_FULLSCREEN;
		if( flags & Flags::Hidden )      sdl2WindowFlags |= SDL_WINDOW_HIDDEN;
		if( flags & Flags::Borderless )  sdl2WindowFlags |= SDL_WINDOW_BORDERLESS;
		if( flags & Flags::Resizeable )  sdl2WindowFlags |= SDL_WINDOW_RESIZABLE;
		if( flags & Flags::Maximized )   sdl2WindowFlags |= SDL_WINDOW_MAXIMIZED;
		if( flags & Flags::Minimized )   sdl2WindowFlags |= SDL_WINDOW_MINIMIZED;
		if( flags & Flags::GrabedInput ) sdl2WindowFlags |= SDL_WINDOW_INPUT_GRABBED;
		if( flags & Flags::HighDPI )     sdl2WindowFlags |= SDL_WINDOW_ALLOW_HIGHDPI;

		if( (!width || !height) && flags & Flags::FullScreen )
		{
			SDL_DisplayMode mode;
			if( SDL_GetDesktopDisplayMode( 0, &mode ) != 0 )
				throw SDL2_ERROR( "Could not get desktop display mode" );
			width = mode.w;
			height = mode.h;
			sdl2WindowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		switch( context )
		{
		case Context::OpenGL2:
			SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
			SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 0 );
			sdl2WindowFlags |= SDL_WINDOW_OPENGL;
			break;
		case Context::OpenGLCore:
			SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
			SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
			SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 0 );
			sdl2WindowFlags |= SDL_WINDOW_OPENGL;
			break;
		case Context::OpenGLCompatibility:
			SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY );
			SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
			SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 0 );
			sdl2WindowFlags |= SDL_WINDOW_OPENGL;
			break;
		case Context::OpenGLES2:
			SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES );
			SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
			SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 0 );
			sdl2WindowFlags |= SDL_WINDOW_OPENGL;
			break;
		case Context::SDL2:
			break;
		}

		this->window = SDL_CreateWindow(
			title.c_str(),          // window title
			SDL_WINDOWPOS_CENTERED, // the x position of the window
			SDL_WINDOWPOS_CENTERED, // the y position of the window
			width, height,          // window width and height
			sdl2WindowFlags
		);
		if( !this->window )
			throw SDL2_ERROR( "Could not create window" );

		{
			SDL_DisplayMode mode;
			SDL_GetCurrentDisplayMode( 0, &mode );
			std::cout << "Screen      : " << SDL_BITSPERPIXEL(mode.format) << "BPP " << mode.w << "x" << mode.h << "@" << mode.refresh_rate << "Hz\n";
		}

		RenderContext::ARenderContext * renderContext = nullptr;

		if( context == Context::SDL2 )
		{
			this->sdlRenderer = SDL_CreateRenderer( this->window, -1, SDL_RENDERER_PRESENTVSYNC );
			if( !this->sdlRenderer )
				throw SDL2_ERROR( "Could not create renderer" );

			renderContext = new RenderContext::SDL2( eventHandler, this->sdlRenderer, this->window );

			SDL_SetRenderDrawColor( this->sdlRenderer, 0, 0, 0, 0 );
			SDL_RenderClear( this->sdlRenderer );
		}
		else
		{
			this->glContext = SDL_GL_CreateContext( this->window );
			if( !this->glContext )
				throw SDL2_ERROR( "Could not create OpenGL context" );
			std::cout << "Vendor      : " << glGetString(GL_VENDOR) << "\n";
			std::cout << "Renderer    : " << glGetString(GL_RENDERER) << "\n";
			std::cout << "Version     : " << glGetString(GL_VERSION) << "\n";
			std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
			std::cout << "Extensions  : " << glGetString(GL_EXTENSIONS) << "\n";

			switch( context )
			{
			case Context::OpenGL2:
			case Context::OpenGLCore:
			case Context::OpenGLCompatibility:
			case Context::OpenGLES2:
				renderContext = new RenderContext::GLES2( eventHandler );
				break;
			default:
				break;
			}
		}

		return renderContext;
	}
};


SDL2::SDL2( const std::string & title, EventHandler * eventHandler ) : AWindow(eventHandler), pImpl( new Impl )
{
	this->context = this->pImpl->initWindow( title, 0, 0, Flags::Maximized | Flags::Resizeable, Context::SDL2, eventHandler );
}


SDL2::SDL2( const std::string & title, SDL2::Context context, EventHandler * eventHandler ) : AWindow(eventHandler), pImpl( new Impl )
{
	this->context = this->pImpl->initWindow( title, 0, 0, Flags::Maximized | Flags::Resizeable, context, eventHandler );
}


SDL2::SDL2( const std::string & title, Flags flags, SDL2::Context context, EventHandler * eventHandler ) : AWindow(eventHandler), pImpl( new Impl )
{
	this->context = this->pImpl->initWindow( title, 0, 0, flags, context, eventHandler );
}


SDL2::SDL2( const std::string & title, unsigned int width, unsigned int height, Flags flags, Context context, EventHandler * eventHandler ) : AWindow(eventHandler), pImpl( new Impl )
{
	this->context = this->pImpl->initWindow( title, width, height, flags, context, eventHandler );
}


SDL2::~SDL2()
{
	delete this->context;

	if( this->pImpl->sdlRenderer )
	{
		SDL_DestroyRenderer( this->pImpl->sdlRenderer );
		SDL_DestroyWindow( this->pImpl->window );
	}
}


void SDL2::processEvents()
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
		case SDL_WINDOWEVENT:
			switch( sdlEvent.window.event )
			{
			case SDL_WINDOWEVENT_RESIZED:
				{
					int w = 0, h = 0;
					SDL_GetWindowSize( this->pImpl->window, &w, &h );
					int size = std::min<int>( w, h );
					if( auto sdlContext = dynamic_cast<RenderContext::SDL2*>(this->context) )
					{
						sdlContext->setScreenTransform(
							glm::mat3(
								0.5f*size, 0.0f,      0.0f,
								0.0f,     -0.5f*size, 0.0f,
								0.5f*w,    0.5f*h,    1.0f
							)
						);
					}
				}
				break;
			}
			break;
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
			}
			break;
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
			}
			break;
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
			}
			break;
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


void SDL2::display()
{
	if( this->pImpl->sdlRenderer )
	{
		SDL_RenderPresent( this->pImpl->sdlRenderer );
		SDL_SetRenderDrawColor( this->pImpl->sdlRenderer, 0, 0, 0, 0 );
		SDL_RenderClear( this->pImpl->sdlRenderer );
	}
}
