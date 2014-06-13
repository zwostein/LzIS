#ifndef _MODEL_NET_AITERATIVEDEEPENINGSEARCH_INCLUDED_
#define _MODEL_NET_AITERATIVEDEEPENINGSEARCH_INCLUDED_


#include <vector>


template< typename T >
class AIterativeDeepeningSearch
{
public:
	virtual bool isGoal( const T * node ) const = 0;

	virtual std::vector< const T * > getSuccessors( const T * node ) const = 0;

	std::vector< std::vector< const T * > > depthLimitedSearch( const T * from, unsigned int maxDepth, unsigned int currentDepth = 0 )
	{
		std::vector< std::vector< const T * > > foundGoals;
		std::vector< const T * > successors = this->getSuccessors( from );
		for( auto & successor : successors )
		{
			if( this->isGoal( successor ) )
				foundGoals.push_back( std::vector< const T * >( {successor,from} ) );
		}
		if( currentDepth >= maxDepth )
			return foundGoals;
		for( auto & successor : successors )
		{
			std::vector< std::vector< const T * > > newGoals = this->depthLimitedSearch( successor, maxDepth, currentDepth + 1 );
			if( newGoals.size() )
			{
				for( auto & goal : newGoals )
					goal.push_back( from );
				foundGoals.insert( foundGoals.end(), newGoals.begin(), newGoals.end() );
			}
		}
		return foundGoals;
	}

	std::vector< std::vector< const T * > > findShortestPaths( const T * from, unsigned int maxDepth )
	{
		std::vector< std::vector< const T * > > paths;
		for( unsigned int depth = 0; depth < maxDepth; depth++ )
		{
			paths = depthLimitedSearch( from, depth );
			if( paths.size() != 0 )
				break;
		}
		return paths;
	}
};


#endif
