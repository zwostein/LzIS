#ifndef _VIEW_ARENDERCONTEXT_INCLUDED_
#define _VIEW_ARENDERCONTEXT_INCLUDED_


#include <string>


class EventHandler;


namespace View
{
	namespace RenderContext
	{
		class ARenderContext
		{
		public:
			ARenderContext( EventHandler * eventHandler = nullptr )
				: eventHandler(eventHandler) {}
			virtual ~ARenderContext() {}

			virtual std::string getName() const = 0;
			virtual void resize( unsigned int width, unsigned int height ) {}

			EventHandler * getEventHandler() const { return eventHandler; }

		private:
			EventHandler * eventHandler;
		};
	}
}


#endif
