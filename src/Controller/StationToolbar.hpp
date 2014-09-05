#ifndef _CONTROLLER_STATIONTOOLBAR_INCLUDED_
#define _CONTROLLER_STATIONTOOLBAR_INCLUDED_


#include <EventSystem.hpp>
#include <Controller/PointerEvent.hpp>

#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

#include <map>


namespace Controller
{
	class StationToolbar :
		public AutoEventSource,
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
			float size;
			glm::mat3x3 transform;
		};

		class NewEvent
		{
		public:
			NewEvent( const StationToolbar & stationToolbar ) : stationToolbar(stationToolbar) {}
			const StationToolbar & getToolbar() const { return stationToolbar; }
		protected:
			const StationToolbar & stationToolbar;
		};

		class DeleteEvent
		{
		public:
			DeleteEvent( const StationToolbar & stationToolbar ) : stationToolbar(stationToolbar) {}
			const StationToolbar & getToolbar() const { return stationToolbar; }
		protected:
			const StationToolbar & stationToolbar;
		};

		StationToolbar( float height, const glm::mat3x3 & transform, EventHandler * eventHandler = nullptr );
		virtual ~StationToolbar();

		virtual void onEvent( const PointerDownEvent & event ) override;
		virtual void onEvent( const PointerUpEvent & event ) override;
		virtual void onEvent( const PointerMotionEvent & event ) override;

		void setTransform( const glm::mat3x3 & transform );

		const glm::vec2 getSize() const { return size; }
		const glm::mat3x3 & getTransform() const { return this->transform; }
		const std::map< ToolType, Tool > & getTools() const { return this->tools; }

		bool addToolType( ToolType type );
		bool removeToolType( ToolType type );

	private:
		glm::vec2 size;
		glm::mat3x3 transform;
		std::map< ToolType, Tool > tools;
		void updateTools();
	};
}


#endif
