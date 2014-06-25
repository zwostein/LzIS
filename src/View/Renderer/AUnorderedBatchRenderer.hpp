#ifndef _VIEW_RENDERER_AUNORDEREDBATCHRENDERER_INCLUDED_
#define _VIEW_RENDERER_AUNORDEREDBATCHRENDERER_INCLUDED_


#include <View/Renderer/ABatchRenderer.hpp>

#include <set>


namespace View
{
	namespace Renderer
	{
		template< typename T >
		class AUnorderedBatchRenderer : public ABatchRenderer< T >
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
