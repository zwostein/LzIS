#ifndef _MODEL_BATCHSTEPNODE_INCLUDED_
#define _MODEL_BATCHSTEPNODE_INCLUDED_


#include <Model/AStepable.hpp>

#include <list>


namespace Model
{
	class BatchStepNode : public AStepable
	{
	private:
		typedef std::list< AStepable * > Stepables;
		Stepables stepables;

	public:
		typedef Stepables::iterator iterator;
		typedef Stepables::const_iterator const_iterator;

		iterator       begin()        noexcept { return stepables.begin(); }
		const_iterator begin()  const noexcept { return stepables.begin(); }
		const_iterator cbegin() const noexcept { return stepables.cbegin(); }
		iterator       end()          noexcept { return stepables.end(); }
		const_iterator end()    const noexcept { return stepables.end(); }
		const_iterator cend()   const noexcept { return stepables.cend(); }

		void remove( AStepable & stepable )
			{ return stepables.remove( &stepable ); }

		void prepend( AStepable & stepable )
			{ return stepables.push_front( &stepable ); }

		void append( AStepable & stepable )
			{ return stepables.push_back( &stepable ); }

		virtual void step() override
			{ for( auto stepable : stepables ) stepable->step(); }
	};
}


#endif
