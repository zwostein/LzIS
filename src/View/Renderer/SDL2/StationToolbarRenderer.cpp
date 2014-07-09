#include <View/Renderer/SDL2/StationToolbarRenderer.hpp>
#include <View/Renderer/SDL2/RenderContext.hpp>
#include <View/Renderer/RenderFactory.hpp>
#include <Resource/Image.hpp>
#include <Resource/ImageFileLoader.hpp>

#include <vector>

#include <glm/trigonometric.hpp>
#include <SDL_render.h>


using namespace View::Renderer::SDL2;


RENDERFACTORY_REGISTER( View::Renderer::SDL2::RenderContext, Controller::StationToolbar, StationToolbarRenderer )


StationToolbarRenderer::StationToolbarRenderer( RenderContext & context ) : context(context)
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
	int w = 0, h = 0;
	SDL_GetWindowSize( this->context.getWindow(), &w, &h );
	for( const Controller::StationToolbar * c : this->getModels() )
	{
		float angle = glm::degrees( glm::atan( c->getRectangle().transform[0][1], c->getRectangle().transform[0][0] ) );
		SDL_Rect rect;
		//TODO: cannot draw distorted quads correctly with sdl if aspect ratio != 1.0
		rect.w = c->getRectangle().size.x * w;
		rect.h = c->getRectangle().size.y * h;
		rect.x = (-0.5 * c->getRectangle().size.x + c->getRectangle().transform[2][0]) * w;
		rect.y = (-0.5 * c->getRectangle().size.y + c->getRectangle().transform[2][1]) * h;
		SDL_RenderCopyEx( this->context.getRenderer(), this->texture, nullptr, &rect, angle, NULL, SDL_FLIP_NONE );


		glm::vec3 bl(-0.5 * c->getRectangle().size.x,-0.5 * c->getRectangle().size.y, 1.0f );
		glm::vec3 br( 0.5 * c->getRectangle().size.x,-0.5 * c->getRectangle().size.y, 1.0f );
		glm::vec3 tr( 0.5 * c->getRectangle().size.x, 0.5 * c->getRectangle().size.y, 1.0f );
		glm::vec3 tl(-0.5 * c->getRectangle().size.x, 0.5 * c->getRectangle().size.y, 1.0f );

		bl = c->getRectangle().transform * bl;
		br = c->getRectangle().transform * br;
		tr = c->getRectangle().transform * tr;
		tl = c->getRectangle().transform * tl;

		glm::vec2 screenSize( w, h );
		bl.x *= screenSize.x;
		bl.y *= screenSize.y;
		br.x *= screenSize.x;
		br.y *= screenSize.y;
		tr.x *= screenSize.x;
		tr.y *= screenSize.y;
		tl.x *= screenSize.x;
		tl.y *= screenSize.y;

		SDL_SetRenderDrawColor( this->context.getRenderer(), 255, 255, 255, 255 );
		SDL_RenderDrawLine( this->context.getRenderer(), bl.x, bl.y, br.x, br.y );
		SDL_RenderDrawLine( this->context.getRenderer(), br.x, br.y, tr.x, tr.y );
		SDL_RenderDrawLine( this->context.getRenderer(), tr.x, tr.y, tl.x, tl.y );
		SDL_RenderDrawLine( this->context.getRenderer(), tl.x, tl.y, bl.x, bl.y );
	}
}
