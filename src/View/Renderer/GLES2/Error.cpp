#include <View/Renderer/GLES2/Error.hpp>

#include <map>


using namespace View::Renderer::GLES2;


static std::map< GLenum, std::string > ErrorStrings =
{
	{ GL_NO_ERROR,                      "No Error"                      },
	{ GL_INVALID_ENUM,                  "Invalid Enum"                  },
	{ GL_INVALID_VALUE,                 "Invalid Value"                 },
	{ GL_INVALID_OPERATION,             "Invalid Operation"             },
	{ GL_INVALID_FRAMEBUFFER_OPERATION, "Invalid Framebuffer Operation" },
	{ GL_OUT_OF_MEMORY,                 "Out Of Memory"                 }
};


std::string Error::getErrorString( GLenum error )
{
	auto i = ErrorStrings.find( error );
	if( i == ErrorStrings.end() )
		return "Unknown Error (" + std::to_string( error ) + ")";
	return i->second;
}
