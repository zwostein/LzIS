#ifndef _VIEW_RENDERER_SDL2_PULSELINKRENDERER_INCLUDED_
#define _VIEW_RENDERER_SDL2_PULSELINKRENDERER_INCLUDED_


#include <View/RenderContext/SDL2.hpp>
#include <View/Renderer/ARenderable.hpp>

#include <Model/Net/PulseLink.hpp>
#include <Model/Net/PulseNode.hpp>

#include <unordered_set>


namespace View
{
	namespace Renderer
	{
		namespace SDL2
		{
			class PulseLinkRenderer :
				public ARenderable,
				public AAutoEventListener< Model::Net::PulseNode::NewLinkEvent >,
				public AAutoEventListener< Model::Net::PulseNode::DeleteLinkEvent >
			{
			public:
				PulseLinkRenderer( RenderContext::SDL2 & context ) :
					AAutoEventListener< Model::Net::PulseNode::NewLinkEvent >( context.getEventHandler() ),
					AAutoEventListener< Model::Net::PulseNode::DeleteLinkEvent >( context.getEventHandler() ),
					context(context)
					{}
				virtual ~PulseLinkRenderer() {}
				virtual void render() const override;

				virtual void onEvent( const Model::Net::PulseNode::NewLinkEvent & event ) override
					{ this->models.insert( &event.link ); }
				virtual void onEvent( const Model::Net::PulseNode::DeleteLinkEvent & event ) override
					{ this->models.erase( &event.link ); }

			private:
				RenderContext::SDL2 & context;
				std::unordered_set< const Model::Net::PulseLink * > models;
			};
		}
	}
}


#endif
