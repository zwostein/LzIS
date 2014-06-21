#ifndef _VIEW_ORDEREDDRAWER_INCLUDED_
#define _VIEW_ORDEREDDRAWER_INCLUDED_


#include "ADrawer.hpp"

#include <map>


namespace View
{
	class OrderedDrawer : public ADrawer
	{
	public:

		virtual bool removeDrawable( const ADrawable * drawable ) override;

		virtual bool addDrawable( const ADrawable * drawable ) override
			{ return addDrawable( drawable, 0 ); }

		bool addDrawable( const ADrawable * drawable, int order );

		const std::multimap< int, const ADrawable * > & getDrawables() const
			{ return drawablesAsValues; }

		virtual void draw() const override;

	private:
		std::multimap< int, const ADrawable * > drawablesAsValues;
		std::map< const ADrawable *, int > drawablesAsKeys;
	};
}


#endif
