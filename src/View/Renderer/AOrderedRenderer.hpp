#ifndef _VIEW_RENDERER_AORDEREDBATCHRENDERER_INCLUDED_
#define _VIEW_RENDERER_AORDEREDBATCHRENDERER_INCLUDED_


#include <View/Renderer/ABatchRenderer.hpp>

#include <map>


namespace View
{
	namespace Renderer
	{
		template< typename T >
		class AOrderedBatchRenderer : public ABatchRenderer< T >
		{
		public:

			virtual bool removeModel( const T & model ) override
			{
				auto it = modelsAsKeys.find( &model );
				if( it == modelsAsKeys.end() )
					return false; // not tracked
				int order = (*it).second;
				modelsAsKeys.erase( it );

				auto itSameOrderRange = modelsAsValues.equal_range( order );
				for( auto itSameOrder = itSameOrderRange.first; itSameOrder != itSameOrderRange.second; ++itSameOrder )
				{
					if( itSameOrder->second == &model )
					{
						modelsAsValues.erase( itSameOrder );
						break;
					}
				}
				return true;
			}

			bool addModel( const T & model, int order )
			{
				auto it = modelsAsKeys.find( &model );
				if( it != modelsAsKeys.end() )
					return false; // already tracked
				modelsAsKeys[&model] = order;
				modelsAsValues.insert( std::pair< int, T * >( order, &model ) );
				return true;
			}

			virtual bool addModel( const T & model ) override
				{ return addModel( &model, 0 ); }

			const std::multimap< int, const T * > & getModels() const
				{ return modelsAsValues; }

		private:
			std::multimap< int, const T * > modelsAsValues;
			std::map< const T *, int > modelsAsKeys;
		};
	}
}


#endif
