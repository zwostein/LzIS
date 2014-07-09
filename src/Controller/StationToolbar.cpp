#include <Controller/StationToolbar.hpp>

#include <glm/gtx/matrix_transform_2d.hpp>

#include <iostream>


using namespace Controller;


StationToolbar::StationToolbar( float height, const glm::mat3x3 & transform, EventHandler * eventHandler ) :
	AAutoEventListener< PointerDownEvent >( eventHandler ),
	AAutoEventListener< PointerUpEvent >( eventHandler ),
	AAutoEventListener< PointerMotionEvent >( eventHandler ),
	height(height)
{
	this->setTransform( transform );
	this->rectangle.size.y = height;
	this->rectangle.size.x = height;
}


StationToolbar::~StationToolbar()
{

}


void StationToolbar::setTransform( const glm::mat3x3 & transform )
{
	this->rectangle.transform = transform;
}


void StationToolbar::updateRectangles()
{
	float toolWidth = height;

	this->rectangle.size.y = height;
	this->rectangle.size.x = toolWidth * this->tools.size();

	std::cout << "Toolbar size: " << this->rectangle.size.x << "x" << this->rectangle.size.y << "\n";

	glm::mat3x3 toolTransform;
	// left-most tool position
	toolTransform = glm::translate( toolTransform, glm::vec2( -0.5 * this->rectangle.size.x, 0.0f ) );

	for( auto & p : this->tools )
	{
		Tool & tool = p.second;
		tool.rectangle.size.x = tool.rectangle.size.y = this->rectangle.size.y;
		tool.rectangle.transform = this->rectangle.transform * toolTransform;
		// advance to next tool position
		toolTransform = glm::translate( toolTransform, glm::vec2( toolWidth, 0.0f ) );
	}
}


bool StationToolbar::addToolType( StationToolbar::ToolType type )
{
	Tool t;
	t.type = type;
	t.state = ToolState::NORMAL;

	bool success = tools.insert( std::pair< ToolType, Tool >( type, t ) ).second;

	updateRectangles();

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
