#ifndef _VIEW_RENDERER_SFML_PULSELINKRENDERER_INCLUDED_
#define _VIEW_RENDERER_SFML_PULSELINKRENDERER_INCLUDED_


#include <View/Renderer/SFML/RenderContext.hpp>
#include <View/Renderer/AUnorderedRenderer.hpp>
#include <Model/Net/PulseLink.hpp>
#include <Model/Net/PulseNode.hpp>


namespace View
{
	namespace Renderer
	{
		namespace SFML
		{
			class PulseLinkRenderer :
				public AUnorderedRenderer< Model::Net::PulseLink >,
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
				virtual void draw() const override;

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
