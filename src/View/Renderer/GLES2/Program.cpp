#include <View/Renderer/GLES2/Program.hpp>
#include <View/Renderer/GLES2/Shader.hpp>
#include <View/Renderer/GLES2/Error.hpp>

#include <exceptions.hpp>

#include <memory>

#include <GLES2/gl2.h>


using namespace View;
using namespace View::Renderer::GLES2;


Program::Program()
{
}


Program::~Program()
{
	if( this->id )
		glDeleteProgram( this->id );
}


void Program::create()
{
	GLES2_ERROR_CHECK_UNHANDLED();
	if( this->id )
	{
		glDeleteProgram( this->id );
		GLES2_ERROR_CHECK("glDeleteProgram");
	}
	this->id = glCreateProgram();
	GLES2_ERROR_CHECK("glCreateProgram");
}


void Program::attach( const Shader & shader )
{
	GLES2_ERROR_CHECK_UNHANDLED();
	glAttachShader( this->id, shader.getID() );
	GLES2_ERROR_CHECK("glAttachShader");
}


void Program::link()
{
	GLES2_ERROR_CHECK_UNHANDLED();
	glLinkProgram( this->id );
	GLES2_ERROR_CHECK("glLinkProgram");

	int isLinked;
	glGetProgramiv( this->id, GL_LINK_STATUS, &isLinked );
	if( !isLinked )
	{
		GLint infoLen = 0;
		glGetProgramiv( this->id, GL_INFO_LOG_LENGTH, &infoLen );

		if( infoLen > 1 )
		{
			std::unique_ptr< GLchar[] > infoLog( new GLchar[infoLen] );
			glGetProgramInfoLog( this->id, infoLen, NULL, infoLog.get() );
			GLES2_ERROR_CHECK("glGetProgramInfoLog");
			std::string log( infoLog.get(), infoLen-1 );
			glDeleteProgram( this->id );
			throw RUNTIME_ERROR
			(
				"Error linking shader program:\n"
				"----------------\n"
				+log+"\n"
				"----------------\n"
			);
		}
		else
		{
			glDeleteProgram( this->id );
			throw RUNTIME_ERROR( "Error linking shader program! (no log generated)\n" );
		}
	}
}


GLint Program::getAttributeLocation( const std::string & name ) const
{
	GLES2_ERROR_CHECK_UNHANDLED();
	GLint location = glGetAttribLocation( this->id, name.c_str() );
	GLES2_ERROR_CHECK("glGetAttribLocation");
	return location;
}


GLint Program::getUniformLocation( const std::string & name ) const
{
	GLES2_ERROR_CHECK_UNHANDLED();
	GLint location = glGetUniformLocation( this->id, name.c_str() );
	GLES2_ERROR_CHECK("glGetUniformLocation");
	return location;
}
