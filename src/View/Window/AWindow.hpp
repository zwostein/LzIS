#ifndef _VIEW_AWINDOW_INCLUDED_
#define _VIEW_AWINDOW_INCLUDED_


#include <View/Renderer/ARenderable.hpp>
#include <View/Renderer/ARenderContext.hpp>

#include <string>


namespace Model
{
	class EventHandler;
}


namespace View
{
	class AWindow : public Renderer::ARenderable
	{
	public:
		AWindow( Model::EventHandler * eventHandler = nullptr ) : eventHandler(eventHandler) {}
		virtual ~AWindow() {}

		virtual std::string getName() const = 0;
		virtual Renderer::ARenderContext * getContext() const = 0;

		Model::EventHandler * getEventHandler() const
			{ return eventHandler; }

		void setRenderRoot( const ARenderable * renderRoot )
			{ this->renderRoot = renderRoot; }
		const ARenderable * getRenderRoot() const
			{ return this->renderRoot; }

	private:
		Model::EventHandler * eventHandler;
		const ARenderable * renderRoot;
	};
}


#endif
