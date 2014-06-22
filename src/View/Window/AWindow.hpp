#ifndef _VIEW_AWINDOW_INCLUDED_
#define _VIEW_AWINDOW_INCLUDED_


#include <View/ADrawable.hpp>
#include <View/Renderer/ARenderContext.hpp>

#include <string>


namespace Model
{
	class EventHandler;
}


namespace View
{
	class AWindow : public ADrawable
	{
	public:
		AWindow( Model::EventHandler * eventHandler = nullptr ) : eventHandler(eventHandler) {}
		virtual ~AWindow() {}

		virtual std::string getName() const = 0;
		virtual Renderer::ARenderContext * getContext() const = 0;

		Model::EventHandler * getEventHandler() const
			{ return eventHandler; }

		void setDrawable( const ADrawable * drawable )
			{ this->drawable = drawable; }
		const ADrawable * getDrawable() const
			{ return this->drawable; }

	private:
		Model::EventHandler * eventHandler;
		const ADrawable * drawable;
	};
}


#endif
