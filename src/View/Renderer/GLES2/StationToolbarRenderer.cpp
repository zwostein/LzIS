#include <View/Renderer/GLES2/StationToolbarRenderer.hpp>
#include <View/RenderContext/GLES2.hpp>
#include <View/Renderer/RendererFactory.hpp>

#include <Resource/Image.hpp>
#include <Resource/ImageFileLoader.hpp>


using namespace View;
using namespace View::Renderer::GLES2;


RENDERERFACTORY_REGISTER_RENDERER( RenderContext::GLES2, StationToolbarRenderer, 0 )


StationToolbarRenderer::StationToolbarRenderer( RenderContext::GLES2 & context ) :
	AAutoEventListener< Controller::StationToolbar::NewEvent >( context.getEventHandler() ),
	AAutoEventListener< Controller::StationToolbar::DeleteEvent >( context.getEventHandler() ),
	context(context)
{
	Resource::RGBAImage * image = Resource::ImageFileLoader::newFromFile<Resource::RGBAImage>("test.png");
	delete image;
}


StationToolbarRenderer::~StationToolbarRenderer()
{
}


void StationToolbarRenderer::render() const
{
	for( const Controller::StationToolbar * c : this->models )
	{
	}
}
