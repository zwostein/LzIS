#include <View/Renderer/SDL2/StationToolbarRenderer.hpp>
#include <View/RenderContext/SDL2.hpp>
#include <View/Renderer/RendererFactory.hpp>
#include <Resource/Image.hpp>
#include <Resource/ImageFileLoader.hpp>

#include <vector>

#include <glm/trigonometric.hpp>
#include <SDL_render.h>


using namespace View::Renderer::SDL2;


RENDERERFACTORY_REGISTER_RENDERER( View::RenderContext::SDL2, StationToolbarRenderer, 0 )


StationToolbarRenderer::StationToolbarRenderer( RenderContext::SDL2 & context ) :
	AAutoEventListener< Controller::StationToolbar::NewEvent >( context.getEventHandler() ),
	AAutoEventListener< Controller::StationToolbar::DeleteEvent >( context.getEventHandler() ),
	context(context)
{
	Resource::RGBAImage * image = Resource::ImageFileLoader::newFromFile<Resource::RGBAImage>("test.png");
	this->texture = SDL_CreateTexture( this->context.getRenderer(), SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, image->getWidth(), image->getHeight() );
	SDL_UpdateTexture( this->texture, NULL, image->getData(), image->getWidth() * 4 );
	SDL_SetTextureBlendMode( this->texture, SDL_BLENDMODE_BLEND );
	delete image;
}


StationToolbarRenderer::~StationToolbarRenderer()
{
	SDL_DestroyTexture( this->texture );
}


void StationToolbarRenderer::render() const
{
	for( const Controller::StationToolbar * c : this->models )
	{
		glm::mat3 finalTransform = this->context.getScreenTransform() * c->getTransform();

		//HACK: applying a transformation matrix to SDL_RenderCopyEx? bad idea! - code below only works for rotation and translation
		SDL_Rect rect;
		glm::vec2 size = glm::vec2( this->context.getScreenTransform() * glm::vec3( c->getSize(), 0.0f ) );
		glm::vec2 pos  = glm::vec2( this->context.getScreenTransform() * glm::vec3( -0.5f*c->getSize() + glm::vec2(c->getTransform()[2]), 1.0f ) );
		rect.w = size.x;
		rect.h = size.y;
		rect.x = pos.x;
		rect.y = pos.y;
		float angle = glm::degrees( glm::atan( finalTransform[0][1], finalTransform[0][0] ) );
		SDL_RenderCopyEx( this->context.getRenderer(), this->texture, nullptr, &rect, angle, nullptr, SDL_FLIP_NONE );

		glm::vec3 bl(-0.5 * c->getSize().x,-0.5 * c->getSize().y, 1.0f );
		glm::vec3 br( 0.5 * c->getSize().x,-0.5 * c->getSize().y, 1.0f );
		glm::vec3 tr( 0.5 * c->getSize().x, 0.5 * c->getSize().y, 1.0f );
		glm::vec3 tl(-0.5 * c->getSize().x, 0.5 * c->getSize().y, 1.0f );
		bl = finalTransform * bl;
		br = finalTransform * br;
		tr = finalTransform * tr;
		tl = finalTransform * tl;
		SDL_SetRenderDrawColor( this->context.getRenderer(), 255, 255, 255, 255 );
		SDL_RenderDrawLine( this->context.getRenderer(), bl.x, bl.y, br.x, br.y );
		SDL_RenderDrawLine( this->context.getRenderer(), br.x, br.y, tr.x, tr.y );
		SDL_RenderDrawLine( this->context.getRenderer(), tr.x, tr.y, tl.x, tl.y );
		SDL_RenderDrawLine( this->context.getRenderer(), tl.x, tl.y, bl.x, bl.y );
	}
}
