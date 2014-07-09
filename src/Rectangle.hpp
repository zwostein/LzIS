#ifndef _RECTANGLE_INCLUDED_
#define _RECTANGLE_INCLUDED_


#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>


struct Rectangle
{
	glm::vec2 size;
	glm::mat3x3 transform;
};


#endif
