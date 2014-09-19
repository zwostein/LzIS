#ifndef _VIEW_RENDERER_GLES2_STATIONTOOLBARRENDERER_INCLUDED_
#define _VIEW_RENDERER_GLES2_STATIONTOOLBARRENDERER_INCLUDED_


#include <View/RenderContext/GLES2.hpp>
#include <View/Renderer/ARenderable.hpp>

#include <View/Renderer/GLES2/Texture2D.hpp>
#include <View/Renderer/GLES2/Program.hpp>

#include <Controller/StationToolbar.hpp>

#include <unordered_set>


namespace View
{
	namespace Renderer
	{
		namespace GLES2
		{
			class StationToolbarRenderer :
				public ARenderable,
				public AAutoEventListener< Controller::StationToolbar::NewEvent >,
				public AAutoEventListener< Controller::StationToolbar::DeleteEvent >
			{
			public:
				StationToolbarRenderer( RenderContext::GLES2 & context );
				virtual ~StationToolbarRenderer();

				virtual void render() const override;

				virtual void onEvent( const Controller::StationToolbar::NewEvent & event ) override
					{ this->models.insert( &event.getToolbar() ); }
				virtual void onEvent( const Controller::StationToolbar::DeleteEvent & event ) override
					{ this->models.erase( &event.getToolbar() ); }

			private:
				RenderContext::GLES2 & context;
				Texture2D texture;
				Program program;
				GLint program_aPosition;
				GLint program_aTexCoord;
				GLint program_uProjection;
				GLint program_uModelView;
				GLint program_uPositionScale;
				GLint program_uTexCoordScale;
				GLint program_uTexture;
				GLuint vertexBuffer;
				std::unordered_set< const Controller::StationToolbar * > models;
			};
		}
	}
}


#endif
