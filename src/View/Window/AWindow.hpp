#ifndef _VIEW_AWINDOW_INCLUDED_
#define _VIEW_AWINDOW_INCLUDED_


#include <EventSystem.hpp>
#include <View/RenderContext/ARenderContext.hpp>

#include <string>


class EventHandler;


namespace View
{
	namespace Window
	{
		class AWindow : public AutoEventSource
		{
		public:
			AWindow( EventHandler * eventHandler = nullptr ) : AutoEventSource(eventHandler) {}
			virtual ~AWindow() {}

			virtual std::string getName() const = 0;
			virtual RenderContext::ARenderContext * getContext() const = 0;
			virtual bool isCloseRequested() const = 0;
			virtual void processEvents() = 0;
			virtual void display() = 0;
		};
	}
}


#endif
