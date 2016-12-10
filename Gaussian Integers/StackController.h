#pragma once
#include <SFML/Window/Event.hpp>
#include "ViewStack.h"

/*	The StackController manipulates the stack by using the method the StackController provides.
	It is the first to respond before sending the events down to other layers, and responsible
	for getting all other layers to draw. The first response it does is "plugged" in with a 
	function pointer. 
*/

class ViewStack;

class StackController {
private:
	// The stack the StackController controls.
	ViewStack* stack;
public:
	StackController(ViewStack* stack) : stack(stack) {};
	// The first response it does, "plugged" in with a function pointer.
	void (*stack_respond) (sf::Event, StackController* const);
	// The response sent down through the first responder and so forth.
	void respond(sf::Event event);
	// Draws all the layers.
	void draw();
};