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


Window::Window( const std::string & title, Model::EventHandler * eventHandler ) : AWindow(eventHandler), pImpl( new Impl )
{
	this->pImpl->renderWindow = new sf::RenderWindow( sf::VideoMode(800, 600), title );
	this->pImpl->renderWindow->setVerticalSyncEnabled( true );

	this->context = new Renderer::SFML::RenderContext( eventHandler, this->pImpl->renderWindow );
}


Window::~Window()
{
	delete static_cast< Renderer::SFML::RenderContext * >(this->context);
	delete this->pImpl->renderWindow;
}


void Window::render() const
{
	this->pImpl->renderWindow->clear( sf::Color::Black );

	if( this->getRenderRoot() )
		this->getRenderRoot()->render();

	this->pImpl->renderWindow->display();
}
