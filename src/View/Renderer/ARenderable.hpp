#ifndef _VIEW_RENDERER_ARENDERABLE_INCLUDED_
#define _VIEW_RENDERER_ARENDERABLE_INCLUDED_


namespace View
{
	namespace Renderer
	{
		class ARenderable
		{
		public:
			virtual ~ARenderable() {}
			virtual void render() const = 0;
		};
	}
}


#endif
