#ifndef _VIEW_SDL2_WINDOW_INCLUDED_
#define _VIEW_SDL2_WINDOW_INCLUDED_


#include "../AWindow.hpp"
#include "../Renderer/ARenderContext.hpp"

#include <string>
#include <memory>


namespace View
{
	namespace SDL2
	{
		class Window : public AWindow
		{
		public:
			Window( const std::string & name );
			virtual ~Window();

			virtual Renderer::ARenderContext * getContext() const override
				{ return context; }

			virtual void setDrawable( const ADrawable * drawable ) override
				{ this->drawable = drawable; }

			virtual const ADrawable * getDrawable() const override
				{ return this->drawable; }

			virtual void draw() const override;

		private:
			class Impl;
			std::unique_ptr< Impl > pImpl;

			const ADrawable * drawable;
			Renderer::ARenderContext * context;
		};
	}
}


#endif
