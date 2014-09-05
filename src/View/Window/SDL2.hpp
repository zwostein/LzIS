#ifndef _VIEW_WINDOW_SDL2_INCLUDED_
#define _VIEW_WINDOW_SDL2_INCLUDED_


#include <View/Window/AWindow.hpp>
#include <View/RenderContext/ARenderContext.hpp>

#include <string>
#include <memory>


namespace View
{
	namespace Window
	{
		class SDL2 : public AWindow
		{
		public:
			enum Flags
			{
				Default     = 0,
				FullScreen  = 1<<0,
				Hidden      = 1<<1,
				Borderless  = 1<<2,
				Resizeable  = 1<<3,
				Maximized   = 1<<4,
				Minimized   = 1<<5,
				GrabedInput = 1<<6,
				HighDPI     = 1<<7
			};


			enum class Context
			{
				SDL2,
				OpenGL2,
				OpenGLCore,
				OpenGLCompatibility,
				OpenGLES2,
			};

			SDL2( const std::string & title, EventHandler * eventHandler = nullptr );
			SDL2( const std::string & title, Context context, EventHandler * eventHandler = nullptr );
			SDL2( const std::string & title, Flags flags, Context context, EventHandler * eventHandler = nullptr );
			SDL2( const std::string & title, unsigned int width, unsigned int height, Flags flags, Context context, EventHandler * eventHandler = nullptr );
			virtual ~SDL2();
			virtual std::string getName() const override { return "SDL2"; }
			virtual RenderContext::ARenderContext * getContext() const override { return context; }
			virtual bool isCloseRequested() const override { return this->closeRequested; }
			virtual void processEvents() override;
			virtual void display() override;

		private:
			class Impl;
			std::unique_ptr< Impl > pImpl;

			RenderContext::ARenderContext * context = nullptr;
			bool closeRequested = false;
		};

		constexpr SDL2::Flags operator|(SDL2::Flags f1, SDL2::Flags f2) { return SDL2::Flags( int(f1)|int(f2) ); }
	}
}


#endif
