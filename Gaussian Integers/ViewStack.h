#pragma once
#include <vector>
#include "ViewLayer.h"
#include "StackController.h"
/*	The ViewStack contains not a stack, but a vector of views, named such as the layers are visually 
	stacked on the screen. The ViewStack can add, flush(delete all), reveal, and hide layers. The ViewStack 
	also holds the first responder. The way the ViewStack controls the layers, and not just hold them,
	is through the StackController.
*/

class ViewLayer;

class ViewStack {
friend class StackController;
private:
	// The layers the ViewStack holds.
	std::vector<ViewLayer*> layers;
public:
	// Besides the StackController, who responds to the input first?
	ViewLayer* first_responder;
	// Pushes the next layer in.
	void push_layer(ViewLayer* layer);
	// Hide and unhide a layer.
	void toggle_layer(std::string title);
	// Clear all layers, usually to bring a new set in.
	void flush_layers();
};