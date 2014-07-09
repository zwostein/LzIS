#ifndef _VIEW_RENDERER_SFML_PULSELINKRENDERER_INCLUDED_
#define _VIEW_RENDERER_SFML_PULSELINKRENDERER_INCLUDED_


#include <View/Renderer/SFML/RenderContext.hpp>
#include <View/Renderer/AUnorderedBatchRenderer.hpp>
#include <Model/Net/PulseLink.hpp>
#include <Model/Net/PulseNode.hpp>


namespace View
{
	namespace Renderer
	{
		namespace SFML
		{
			class PulseLinkRenderer :
				public AUnorderedBatchRenderer< Model::Net::PulseLink >,
				public AAutoEventListener< Model::Net::PulseNode::NewLinkEvent >,
				public AAutoEventListener< Model::Net::PulseNode::DeleteLinkEvent >
			{
			public:
				PulseLinkRenderer( RenderContext & context ) :
					AAutoEventListener< Model::Net::PulseNode::NewLinkEvent >( context.getEventHandler() ),
					AAutoEventListener< Model::Net::PulseNode::DeleteLinkEvent >( context.getEventHandler() ),
					context(context)
					{}
				virtual ~PulseLinkRenderer() {}
				virtual void render() const override;

				virtual void onEvent( const Model::Net::PulseNode::NewLinkEvent & event ) override
					{ this->addModel( event.link ); }
				virtual void onEvent( const Model::Net::PulseNode::DeleteLinkEvent & event ) override
					{ this->removeModel( event.link ); }

			private:
				RenderContext & context;
			};
		}
	}
}


#endif
