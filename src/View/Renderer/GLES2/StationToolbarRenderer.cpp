#include <View/Renderer/GLES2/StationToolbarRenderer.hpp>
#include <View/RenderContext/GLES2.hpp>

#include <View/Renderer/GLES2/Texture2D.hpp>
#include <View/Renderer/GLES2/Program.hpp>
#include <View/Renderer/GLES2/Shader.hpp>

#include <View/Renderer/RendererFactory.hpp>

#include <Resource/Image.hpp>
#include <Resource/ImageFileLoader.hpp>

#include <exceptions.hpp>

#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>

#include <iostream>

#include <stddef.h>


using namespace View;
using namespace View::Renderer::GLES2;


RENDERERFACTORY_REGISTER_RENDERER( RenderContext::GLES2, StationToolbarRenderer, 0 )


static const char * vertexShaderSRC =
R"GLSL(#version 100
varying vec2 vTexCoord;

uniform mat4 uProjection;
uniform mat3 uModelView;
uniform vec2 uPositionScale;
uniform vec2 uTexCoordScale;

attribute vec2 aPosition;
attribute vec2 aTexCoord;

void main()
{
	gl_Position = uProjection * vec4( uModelView * vec3( aPosition * uPositionScale, 1.0 ), 1.0 );
	vTexCoord = aTexCoord * uTexCoordScale;
}
)GLSL";


static const char * fragmentShaderSRC =
R"GLSL(#version 100
varying lowp vec2 vTexCoord;

uniform sampler2D uTexture;

void main()
{
	gl_FragColor = texture2D( uTexture, vTexCoord );
}
)GLSL";


struct Vertex
{
	glm::vec2 position;
	glm::vec2 texCoord;
};


static Vertex centeredQuad[4] =
{
	{ {-0.5,-0.5}, { 0, 0} },
	{ { 0.5,-0.5}, { 1, 0} },
	{ {-0.5, 0.5}, { 0, 1} },
	{ { 0.5, 0.5}, { 1, 1} }
};


StationToolbarRenderer::StationToolbarRenderer( RenderContext::GLES2 & context ) :
	AAutoEventListener< Controller::StationToolbar::NewEvent >( context.getEventHandler() ),
	AAutoEventListener< Controller::StationToolbar::DeleteEvent >( context.getEventHandler() ),
	context(context)
{
	Resource::RGBAImage * image = Resource::ImageFileLoader::newFromFile<Resource::RGBAImage>("test.png");
	this->texture.load( *image );
	delete image;

	this->program.create();
	this->program.attach( Shader( GL_VERTEX_SHADER, vertexShaderSRC ) );
	this->program.attach( Shader( GL_FRAGMENT_SHADER, fragmentShaderSRC ) );
	this->program.link();

	this->program_aPosition = this->program.getAttributeLocation( "aPosition" );
	if( this->program_aPosition == -1 )
		throw RUNTIME_ERROR( "Attribute aPosition not found in shader!" );

	this->program_aTexCoord = this->program.getAttributeLocation( "aTexCoord" );
	if( this->program_aTexCoord == -1 )
		throw RUNTIME_ERROR( "Attribute aTexCoord not found in shader!" );

	this->program_uProjection = this->program.getUniformLocation( "uProjection" );
	if( this->program_uProjection == -1 )
		throw RUNTIME_ERROR( "Uniform uProjection not found in shader!" );

	this->program_uModelView = this->program.getUniformLocation( "uModelView" );
	if( this->program_uModelView == -1 )
		throw RUNTIME_ERROR( "Uniform uModelView not found in shader!" );

	this->program_uPositionScale = this->program.getUniformLocation( "uPositionScale" );
	if( this->program_uPositionScale == -1 )
		throw RUNTIME_ERROR( "Uniform uPositionScale not found in shader!" );

	this->program_uTexCoordScale = this->program.getUniformLocation( "uTexCoordScale" );
	if( this->program_uTexCoordScale == -1 )
		throw RUNTIME_ERROR( "Uniform uTexCoordScale not found in shader!" );

	this->program_uTexture = this->program.getUniformLocation( "uTexture" );
	if( this->program_uTexture == -1 )
		throw RUNTIME_ERROR( "Uniform uTexture not found in shader!" );

	glGenBuffers( 1, &this->vertexBuffer);
	glBindBuffer( GL_ARRAY_BUFFER, this->vertexBuffer );
	glBufferData( GL_ARRAY_BUFFER, sizeof(centeredQuad), centeredQuad, GL_STATIC_DRAW );
}


StationToolbarRenderer::~StationToolbarRenderer()
{
}


void StationToolbarRenderer::render() const
{
	this->program.use();
	glUniformMatrix4fv( this->program_uProjection, 1, GL_FALSE, glm::value_ptr(this->context.getProjection()) );

	glActiveTexture( GL_TEXTURE0 );
	glUniform1i( this->program_uTexture, 0 );
	this->texture.bind();

	glBindBuffer( GL_ARRAY_BUFFER, this->vertexBuffer );
	glVertexAttribPointer( this->program_aPosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,position) );
	glVertexAttribPointer( this->program_aTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex,texCoord) );
	glEnableVertexAttribArray( this->program_aPosition );
	glEnableVertexAttribArray( this->program_aTexCoord );

	for( const Controller::StationToolbar * c : this->models )
	{
		for( const auto t : c->getTools() )
		{
			const Controller::StationToolbar::Tool & tool = t.second;
			glUniformMatrix3fv( this->program_uModelView, 1, GL_FALSE, glm::value_ptr(tool.transform) );
			glUniform2f( this->program_uPositionScale, tool.size, tool.size );
			glUniform2f( this->program_uTexCoordScale, 1, 1 );
			glDrawArrays( GL_TRIANGLE_STRIP, 0, sizeof(centeredQuad)/sizeof(Vertex) );
		}
		/*
		glUniformMatrix3fv( this->program_uModelView, 1, GL_FALSE, glm::value_ptr(c->getTransform()) );
		glUniform2f( this->program_uPositionScale, c->getSize().x, c->getSize().y );
		glUniform2f( this->program_uTexCoordScale, 1, 1 );
		glDrawArrays( GL_TRIANGLE_STRIP, 0, sizeof(centeredQuad)/sizeof(Vertex) );
		*/
	}
}
