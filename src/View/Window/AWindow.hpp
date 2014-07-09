#ifndef _VIEW_AWINDOW_INCLUDED_
#define _VIEW_AWINDOW_INCLUDED_


#include <EventSystem.hpp>
#include <View/Renderer/ARenderContext.hpp>
#include <View/Renderer/ARenderable.hpp>

#include <string>


class EventHandler;


namespace View
{
	class AWindow : public AutoEventSource
	{
	public:
		AWindow( EventHandler * eventHandler = nullptr ) : AutoEventSource(eventHandler) {}
		virtual ~AWindow() {}

		virtual std::string getName() const = 0;
		virtual Renderer::ARenderContext * getContext() const = 0;
		virtual bool isCloseRequested() const = 0;
		virtual void processEvents() = 0;
		virtual void display() = 0;
	};
}


#endif
