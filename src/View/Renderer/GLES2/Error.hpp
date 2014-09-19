#ifndef _VIEW_RENDERER_GLES2_ERROR_INCLUDED_
#define _VIEW_RENDERER_GLES2_ERROR_INCLUDED_


#include <string>
#include <stdexcept>

#include <GLES2/gl2.h>


#define GLES2_ERROR( error, what ) \
	::View::Renderer::GLES2::Error( (error), std::string(__PRETTY_FUNCTION__) + std::string(": ") + (what) )

#ifdef NDEBUG
	#define GLES2_ERROR_CHECK_UNHANDLED()
	#define GLES2_ERROR_CHECK( what )
	#define GLES2_ERROR_CLEAR()
#else
	#define GLES2_ERROR_CHECK_UNHANDLED() \
		::View::Renderer::GLES2::Error::check( std::string(__PRETTY_FUNCTION__) + std::string(": Unhandled previous error") )
	#define GLES2_ERROR_CHECK( what ) \
		::View::Renderer::GLES2::Error::check( std::string(__PRETTY_FUNCTION__) + std::string(": ") + (what) )
	#define GLES2_ERROR_CLEAR() \
		::View::Renderer::GLES2::Error::clear()
#endif


namespace View
{
	namespace Renderer
	{
		namespace GLES2
		{
			class Error : public std::runtime_error
			{
			public:
				static std::string getErrorString( GLenum error );

				static void check()
				{
					GLenum error = glGetError();
					if( error )
						throw Error( error );
				}

				static void check( const std::string & what )
				{
					GLenum error = glGetError();
					if( error )
						throw Error( error, what );
				}

				static void clear()
				{
					glGetError();
				}

				Error( GLenum error )
					: std::runtime_error( this->getErrorString( error ) )
				{}

				Error( GLenum error, const std::string & what )
					: std::runtime_error( what + ": " + this->getErrorString( error ) )
				{}

				virtual ~Error() {}
			};
		}
	}
}


#endif
