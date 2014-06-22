#ifndef _VIEW_RENDERER_ARENDERCONTEXT_INCLUDED_
#define _VIEW_RENDERER_ARENDERCONTEXT_INCLUDED_


#include <string>


namespace Model
{
	class EventHandler;
}


namespace View
{
	namespace Renderer
	{
		class ARenderContext
		{
		public:
			ARenderContext( Model::EventHandler * eventHandler = nullptr ) : eventHandler(eventHandler) {}
			virtual ~ARenderContext() {}

			virtual std::string getName() const = 0;

			Model::EventHandler * getEventHandler() const { return eventHandler; }

		private:
			Model::EventHandler * eventHandler;
		};
	}
}


#endif
