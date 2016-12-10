#include "StackController.h"

void StackController::respond(sf::Event event) {
	//stack_respond(event, this);
	stack->first_responder->respond(event);
}

void StackController::draw() {
	for (ViewLayer* layer : stack->layers) {
		layer->draw();
	}
}
