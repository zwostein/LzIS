#include <Controller/StationToolbar.hpp>

#include <glm/gtx/matrix_transform_2d.hpp>

#include <iostream>


using namespace Controller;


StationToolbar::StationToolbar( float height, const glm::mat3x3 & transform, EventHandler * eventHandler ) :
	AutoEventSource( eventHandler ),
	AAutoEventListener< PointerDownEvent >( eventHandler ),
	AAutoEventListener< PointerUpEvent >( eventHandler ),
	AAutoEventListener< PointerMotionEvent >( eventHandler )
{
	this->setTransform( transform );
	this->size.y = height;
	this->size.x = height;
	this->dispatch( NewEvent(*this) );
}


StationToolbar::~StationToolbar()
{
	this->dispatch( DeleteEvent(*this) );
}


void StationToolbar::setTransform( const glm::mat3x3 & transform )
{
	this->transform = transform;
	this->updateTools();
}


void StationToolbar::updateTools()
{
	float toolSize = this->size.y;
	this->size.x = toolSize * this->tools.size();

	glm::mat3x3 toolTransform;
	// left-most tool position
	toolTransform = glm::translate( toolTransform, glm::vec2( -0.5 * (this->size.x - toolSize), 0.0f ) );

	for( auto & p : this->tools )
	{
		Tool & tool = p.second;
		tool.size = toolSize;
		tool.transform = this->transform * toolTransform;
		// advance to next tool position
		toolTransform = glm::translate( toolTransform, glm::vec2( toolSize, 0.0f ) );
	}
}


bool StationToolbar::addToolType( StationToolbar::ToolType type )
{
	Tool t;
	t.type = type;
	t.state = ToolState::NORMAL;

	bool success = tools.insert( std::pair< ToolType, Tool >( type, t ) ).second;

	updateTools();

	return success;
}


bool StationToolbar::removeToolType( StationToolbar::ToolType type )
{
	return tools.erase( type );
}


void StationToolbar::onEvent( const PointerMotionEvent & event )
{

}


void StationToolbar::onEvent( const PointerUpEvent & event )
{

}


void StationToolbar::onEvent( const PointerDownEvent & event )
{

}
