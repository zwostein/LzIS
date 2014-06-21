#include "OrderedDrawer.hpp"


using namespace View;


bool OrderedDrawer::removeDrawable( const ADrawable * drawable )
{
	auto it = drawablesAsKeys.find( drawable );
	if( it == drawablesAsKeys.end() )
		return false; // not tracked
	int order = (*it).second;
	drawablesAsKeys.erase( it );

	auto itSameOrderRange = drawablesAsValues.equal_range( order );
	for( auto itSameOrder = itSameOrderRange.first; itSameOrder != itSameOrderRange.second; ++itSameOrder )
	{
		if( itSameOrder->second == drawable )
		{
			drawablesAsValues.erase( itSameOrder );
			break;
		}
	}
	return true;
}


bool OrderedDrawer::addDrawable( const ADrawable * drawable, int order )
{
	auto it = drawablesAsKeys.find( drawable );
	if( it != drawablesAsKeys.end() )
		return false; // already tracked
	drawablesAsKeys[drawable] = order;
	drawablesAsValues.insert( std::pair< int, const ADrawable * >( order, drawable ) );
	return true;
}


void OrderedDrawer::draw() const
{
	for( const auto d : this->getDrawables() )
	{
		d.second->draw();
	}
}
