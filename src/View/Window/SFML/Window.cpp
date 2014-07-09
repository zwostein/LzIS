#include <View/Window/SFML/Window.hpp>
#include <View/Renderer/SFML/RenderContext.hpp>

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


Window::Window( const std::string & title, EventHandler * eventHandler ) : AWindow(eventHandler), pImpl( new Impl )
{
	this->pImpl->renderWindow = new sf::RenderWindow( sf::VideoMode(800, 600), title );
	this->pImpl->renderWindow->setVerticalSyncEnabled( true );

	this->context = new Renderer::SFML::RenderContext( eventHandler, this->pImpl->renderWindow );

	this->pImpl->renderWindow->clear( sf::Color::Black );
}


Window::~Window()
{
	delete static_cast< Renderer::SFML::RenderContext * >(this->context);
	delete this->pImpl->renderWindow;
}


bool Window::isCloseRequested() const
{
	return !this->pImpl->renderWindow->isOpen();
}


void Window::processEvents()
{
	sf::Event event;
	while( this->pImpl->renderWindow->pollEvent(event) )
	{
		switch( event.type )
		{
		case sf::Event::Closed:
			this->pImpl->renderWindow->close();
			break;
		default:
			break;
		}
	}
}


void Window::display()
{
	this->pImpl->renderWindow->display();
	this->pImpl->renderWindow->clear( sf::Color::Black );
}
