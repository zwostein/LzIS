#include "Window.hpp"
#include "../Renderer/SFML/RenderContext.hpp"

#include <iostream>
#include <stdexcept>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


using namespace View::SFML;


class Window::Impl
{
public:
	sf::RenderWindow * renderWindow;
};


Window::Window( const std::string & name ) : pImpl( new Impl )
{
	this->pImpl->renderWindow = new sf::RenderWindow( sf::VideoMode(800, 600), name );
	this->pImpl->renderWindow->setVerticalSyncEnabled( true );

	this->context = new Renderer::SFML::RenderContext( this->pImpl->renderWindow );
}


Window::~Window()
{
	delete static_cast< Renderer::SFML::RenderContext * >(this->context);
	delete this->pImpl->renderWindow;
}


void Window::draw() const
{
	this->pImpl->renderWindow->clear( sf::Color::Black );

	if( this->drawable )
		this->drawable->draw();

	this->pImpl->renderWindow->display();
}
