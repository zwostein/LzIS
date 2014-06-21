#ifndef _VIEW_RENDERER_AUNORDEREDRENDERER_INCLUDED_
#define _VIEW_RENDERER_AUNORDEREDRENDERER_INCLUDED_


#include "ARenderer.hpp"

#include <set>


namespace View
{
	namespace Renderer
	{
		template< typename T >
		class AUnorderedRenderer : public ARenderer< T >
		{
		public:

			virtual bool addModel( const T & model ) override
				{ return models.insert( &model ).second; }

			virtual bool removeModel( const T & model ) override
				{ return models.erase( &model ); }

			const std::set< const T * > & getModels() const
				{ return models; }

		private:
			std::set< const T * > models;
		};
	}
}


#endif
