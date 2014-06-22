#ifndef _CONTROLLER_APOINTERPROVIDER_INCLUDED_
#define _CONTROLLER_APOINTERPROVIDER_INCLUDED_


#include <Controller/APointerListener.hpp>

#include <set>


namespace Controller
{
	class APointerProvider
	{
	public:
		bool addPointerListener( APointerListener * listener )
		{
			return listeners.insert( listener ).second;
		}

		bool removePointerListener( APointerListener * listener )
		{
			return listeners.erase( listener );
		}

	protected:
		void pointerEvent( const PointerEvent & event )
		{
			for( auto listener : listeners )
				listener->pointerEvent( event );
		}

	private:
		std::set< APointerListener * > listeners;
	};
}


#endif
