#include <View/Renderer/GLES2/Shader.hpp>
#include <View/Renderer/GLES2/Error.hpp>

#include <exceptions.hpp>

#include <memory>

#include <GLES2/gl2.h>


using namespace View;
using namespace View::Renderer::GLES2;


Shader::Shader()
{
}


Shader::Shader( GLenum type, const std::string & source )
{
	this->load( type, source );
}


Shader::~Shader()
{
	if( this->id )
		glDeleteShader( this->id );
}


void Shader::load( GLenum type, const std::string & source )
{
	GLES2_ERROR_CHECK_UNHANDLED();

	if( this->id )
	{
		glDeleteShader( this->id );
		GLES2_ERROR_CHECK("glDeleteShader");
	}

	GLboolean shaderCompilerAvailable;
	glGetBooleanv( GL_SHADER_COMPILER, &shaderCompilerAvailable );
	if( !shaderCompilerAvailable )
		throw RUNTIME_ERROR( "Shader compiler not available" );

	this->id = glCreateShader( type );
	if( !this->id )
		throw GLES2_ERROR( glGetError(), "glCreateShader" );

	const GLchar * string = source.c_str();
	glShaderSource( this->id, 1, &string, nullptr );
	GLES2_ERROR_CHECK("glShaderSource");

	glCompileShader( this->id );
	GLES2_ERROR_CHECK("glCompileShader");

	GLint compiled;
	glGetShaderiv( this->id, GL_COMPILE_STATUS, &compiled );
	if( !compiled )
	{
		GLint infoLen = 0;
		glGetShaderiv( this->id, GL_INFO_LOG_LENGTH, &infoLen );
		if( infoLen > 1 )
		{
			std::unique_ptr< GLchar[] > infoLog( new GLchar[infoLen] );
			glGetShaderInfoLog( this->id, infoLen, NULL, infoLog.get() );
			GLES2_ERROR_CHECK("glGetShaderInfoLog");
			std::string log( infoLog.get(), infoLen-1 );
			glDeleteShader( this->id );
			throw RUNTIME_ERROR
			(
				"Error compiling shader:\n"
				"----------------\n"
				+source+"\n"
				"--------\n"
				"Log:\n"
				"--------\n"
				+log+"\n"
				"----------------\n"
			);
		}
		else
		{
			glDeleteShader( this->id );
			throw RUNTIME_ERROR
			(
				"Error compiling shader (no log generated):\n"
				"----------------\n"
				+source+"\n"
				"----------------\n"
			);
		}
	}
}
