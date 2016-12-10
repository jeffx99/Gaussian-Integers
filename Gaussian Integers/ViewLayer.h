#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "ViewStack.h"

/*	The ViewLayer is one of the many layers stacked together on the screen, which can respond to events
	and draw itself. 
*/
class ViewLayer {
friend class ViewStack;
protected:
	// The window this layer draws into.
	sf::RenderWindow* win;
	// The view that the layer will be drawn onto.
	sf::View view;
	// If the layer does not respond to an event or for some other reason, it can pass an event to this layer.
	ViewLayer* next_responder;
	// The name by which the layer is referred to when hiding and removing.
	std::string title;
	// Is the layer invisible and unresponsive?
	bool hidden;
public:
	// How will the layer react to an event?
	virtual void respond(sf::Event event) = 0;
	// How will the layer draw itself in its view?
	virtual void draw() = 0;
};