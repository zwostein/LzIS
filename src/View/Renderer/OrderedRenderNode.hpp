#ifndef _VIEW_RENDERER_ORDEREDRENDERNODE_INCLUDED_
#define _VIEW_RENDERER_ORDEREDRENDERNODE_INCLUDED_


#include <View/Renderer/ARenderNode.hpp>

#include <map>


namespace View
{
	namespace Renderer
	{
		class OrderedRenderNode : public ARenderNode
		{
		public:

			virtual bool removeRenderable( const ARenderable * renderable ) override;

			virtual bool addRenderable( const ARenderable * renderable ) override
				{ return addRenderable( renderable, 0 ); }

			bool addRenderable( const ARenderable * renderable, int order );

			const std::multimap< int, const ARenderable * > & getRenderables() const
				{ return renderablesAsValues; }

			virtual void render() const override;

		private:
			std::multimap< int, const ARenderable * > renderablesAsValues;
			std::map< const ARenderable *, int > renderablesAsKeys;
		};
	}
}


#endif
