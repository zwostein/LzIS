#ifndef _CONTROLLER_STATIONTOOLBAR_INCLUDED_
#define _CONTROLLER_STATIONTOOLBAR_INCLUDED_


#include <Rectangle.hpp>
#include <EventSystem.hpp>
#include <Controller/PointerEvent.hpp>

#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

#include <map>


namespace Controller
{
	class StationToolbar :
		public AAutoEventListener< PointerDownEvent >,
		public AAutoEventListener< PointerUpEvent >,
		public AAutoEventListener< PointerMotionEvent >
	{
	public:
		enum ToolType
		{
			SOLARPLANT_CREATOR,
			PHASER_CREATOR,
			REMOVER
		};

		enum ToolState
		{
			NORMAL,
			ACTIVE
		};

		struct Tool
		{
			ToolType type;
			ToolState state;
			Rectangle rectangle;
		};

		StationToolbar( float height, const glm::mat3x3 & transform, EventHandler * eventHandler = nullptr );
		virtual ~StationToolbar();

		virtual void onEvent( const PointerDownEvent & event ) override;
		virtual void onEvent( const PointerUpEvent & event ) override;
		virtual void onEvent( const PointerMotionEvent & event ) override;

		void setTransform( const glm::mat3x3 & transform );

		const float getHeight() const { return height; }
		const Rectangle & getRectangle() const { return this->rectangle; }
		const std::map< ToolType, Tool > & getTools() const { return this->tools; }

		bool addToolType( ToolType type );
		bool removeToolType( ToolType type );

	private:
		float height;
		Rectangle rectangle;
		std::map< ToolType, Tool > tools;
		void updateRectangles();
	};
}


#endif
