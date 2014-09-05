#ifndef _VIEW_RENDERER_BATCHRENDERNODE_INCLUDED_
#define _VIEW_RENDERER_BATCHRENDERNODE_INCLUDED_


#include <View/Renderer/ARenderable.hpp>

#include <list>


namespace View
{
	namespace Renderer
	{
		class BatchRenderNode : public ARenderable
		{
		private:
			typedef std::list< const ARenderable * > Renderables;
			Renderables renderables;

		public:
			typedef Renderables::iterator iterator;
			typedef Renderables::const_iterator const_iterator;

			iterator       begin()        noexcept { return renderables.begin(); }
			const_iterator begin()  const noexcept { return renderables.begin(); }
			const_iterator cbegin() const noexcept { return renderables.cbegin(); }
			iterator       end()          noexcept { return renderables.end(); }
			const_iterator end()    const noexcept { return renderables.end(); }
			const_iterator cend()   const noexcept { return renderables.cend(); }

			void remove( const ARenderable & renderable )
				{ return renderables.remove( &renderable ); }

			void prepend( const ARenderable & renderable )
				{ return renderables.push_front( &renderable ); }

			void append( const ARenderable & renderable )
				{ return renderables.push_back( &renderable ); }

			virtual void render() const override
				{ for( auto renderable : renderables ) renderable->render(); }
		};
	}
}


#endif
