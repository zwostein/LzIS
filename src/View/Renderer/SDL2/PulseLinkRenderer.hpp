#ifndef _VIEW_RENDERER_SDL2_PULSELINKRENDERER_INCLUDED_
#define _VIEW_RENDERER_SDL2_PULSELINKRENDERER_INCLUDED_


#include <View/Renderer/SDL2/RenderContext.hpp>
#include <View/Renderer/AUnorderedBatchRenderer.hpp>
#include <Model/Net/PulseLink.hpp>
#include <Model/Net/PulseNode.hpp>


namespace View
{
	namespace Renderer
	{
		namespace SDL2
		{
			class PulseLinkRenderer :
				public AUnorderedBatchRenderer< Model::Net::PulseLink >,
				public Model::AAutoEventListener< Model::Net::PulseNode::NewLinkEvent >,
				public Model::AAutoEventListener< Model::Net::PulseNode::DeleteLinkEvent >
			{
			public:
				PulseLinkRenderer( RenderContext & context ) :
					Model::AAutoEventListener< Model::Net::PulseNode::NewLinkEvent >( context.getEventHandler() ),
					Model::AAutoEventListener< Model::Net::PulseNode::DeleteLinkEvent >( context.getEventHandler() ),
					context(context)
					{}
				virtual ~PulseLinkRenderer() {}
				virtual void render() const override;

				virtual void onEvent( const Model::Net::PulseNode::NewLinkEvent & event )
					{ this->addModel( event.link ); }
				virtual void onEvent( const Model::Net::PulseNode::DeleteLinkEvent & event )
					{ this->removeModel( event.link ); }

			private:
				RenderContext & context;
			};
		}
	}
}


#endif
