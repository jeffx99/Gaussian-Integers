#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "StackController.h"
#include "ViewStack.h"
#include "ViewLayer.h"
#include "ComplexPlaneLayer.h"


int main() {
	// Creates the RenderWindow.
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Gaussian Integers", sf::Style::Titlebar|sf::Style::Close);

	// Create the ViewStack and Stack Controller
	ViewStack stack;
	StackController control(&stack);

	ComplexPlaneLayer complex_plane(&window);
	stack.push_layer(&complex_plane);

	stack.first_responder = &complex_plane;
	// The event loop.
	while (window.isOpen()) {
		sf::Event event;
		// Handles all events in this loop.
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			control.respond(event);
		}
		control.draw();
		window.display();
		window.clear(sf::Color(127,127,127,255));
	}

	return 0;
}
