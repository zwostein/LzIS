#ifndef _VIEW_SFML_WINDOW_INCLUDED_
#define _VIEW_SFML_WINDOW_INCLUDED_


#include <View/Window/AWindow.hpp>
#include <View/Renderer/ARenderContext.hpp>

#include <string>
#include <memory>


namespace View
{
	namespace SFML
	{
		class Window : public AWindow
		{
		public:
			Window( const std::string & title, EventHandler * eventHandler = nullptr );
			virtual ~Window();

			virtual std::string getName() const override
				{ return "SFML"; }

			virtual Renderer::ARenderContext * getContext() const override
				{ return context; }

			virtual bool isCloseRequested() const override;
			virtual void processEvents() override;
			virtual void display() override;

		private:
			class Impl;
			std::unique_ptr< Impl > pImpl;

			Renderer::ARenderContext * context;
		};
	}
}


#endif
