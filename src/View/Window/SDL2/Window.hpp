#ifndef _VIEW_SDL2_WINDOW_INCLUDED_
#define _VIEW_SDL2_WINDOW_INCLUDED_


#include <View/Window/AWindow.hpp>
#include <View/Renderer/ARenderContext.hpp>

#include <string>
#include <memory>


namespace View
{
	namespace SDL2
	{
		class Window : public AWindow
		{
		public:
			Window( const std::string & title, Model::EventHandler * eventHandler = nullptr );
			virtual ~Window();

			virtual std::string getName() const override
				{ return "SDL2"; }

			virtual Renderer::ARenderContext * getContext() const override
				{ return context; }

			virtual void render() const override;

		private:
			class Impl;
			std::unique_ptr< Impl > pImpl;

			Renderer::ARenderContext * context;
		};
	}
}


#endif
