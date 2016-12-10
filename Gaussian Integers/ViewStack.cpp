#include "ViewStack.h"

void ViewStack::push_layer(ViewLayer* layer) {
	layers.push_back(layer);
}

void ViewStack::toggle_layer(std::string title) {
	for (ViewLayer* layer : layers) {
		if (layer->title == title) layer->hidden = !layer->hidden;
	}
}

void ViewStack::flush_layers() {
	layers.clear();
}
