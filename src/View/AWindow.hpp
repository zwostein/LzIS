#ifndef _VIEW_AWINDOW_INCLUDED_
#define _VIEW_AWINDOW_INCLUDED_


#include "ADrawable.hpp"
#include "Renderer/ARenderContext.hpp"


namespace View
{
	class AWindow : public ADrawable
	{
	public:
		virtual Renderer::ARenderContext * getContext() const = 0;
		virtual void setDrawable( const ADrawable * drawable ) = 0;
		virtual const ADrawable * getDrawable() const = 0;
	};
}


#endif
