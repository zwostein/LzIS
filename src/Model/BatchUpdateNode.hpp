#ifndef _MODEL_BATCHUPDATENODE_INCLUDED_
#define _MODEL_BATCHUPDATENODE_INCLUDED_


#include <Model/AUpdateable.hpp>

#include <list>


namespace Model
{
	class BatchUpdateNode : public AUpdateable
	{
	private:
		typedef std::list< AUpdateable * > Updateables;
		Updateables updateables;

	public:
		typedef Updateables::iterator iterator;
		typedef Updateables::const_iterator const_iterator;

		iterator       begin()        noexcept { return updateables.begin(); }
		const_iterator begin()  const noexcept { return updateables.begin(); }
		const_iterator cbegin() const noexcept { return updateables.cbegin(); }
		iterator       end()          noexcept { return updateables.end(); }
		const_iterator end()    const noexcept { return updateables.end(); }
		const_iterator cend()   const noexcept { return updateables.cend(); }

		void remove( AUpdateable & updateable )
			{ return updateables.remove( &updateable ); }

		void prepend( AUpdateable & updateable )
			{ return updateables.push_front( &updateable ); }

		void append( AUpdateable & updateable )
			{ return updateables.push_back( &updateable ); }

		virtual void update( double delta ) override
			{ for( auto updateable : updateables ) updateable->update( delta ); }
	};
}


#endif
