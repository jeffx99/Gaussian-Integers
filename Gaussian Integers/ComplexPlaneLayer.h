#pragma once
#include "ViewLayer.h"
#include <vector>
#include <SFML/Graphics.hpp>

#define AMOUNT 4000

class ComplexPlaneLayer : public ViewLayer {
private:
	// The point in the complex plane on top of the point in the top left of the window.
	sf::Vector2f anchor = sf::Vector2f(-4, 3);
	// The scale of the graph, defines distance between gridlines
	float zoom = 1;
	// The amount by which we zoom in and out per scroll tick
	float zoom_tick = 0.05;
	// The bounds to zooming
	float zoom_max = 15;
	float zoom_min = 0.25;
	// The conversion factor from the units in the plane to pixels
	int factor = 128;
	// The gridlines, there are 16 of them.
	sf::Vertex vlines[18] = {};
	sf::Vertex hlines[14] = {};
	// The list of primes held in a bool vector, 
	bool primes[AMOUNT];
	// The vector of gaussian primes
	std::vector<sf::Vector2i> gaussian_primes;
	// The recorded mouse position on the last frame
	sf::Vector2i last_mouse = sf::Vector2i(-1,-1);
	// The recorded mouse position this frame
	sf::Vector2i this_mouse;
	// Has a drag started?
	bool drag = false;
	// How many times slower should a drag be? 1 is ideal.
	float drag_factor = 1.0;
	// What was the last magnitude used to call generate_gaussian_primes?
	int last_magnitude = 3000;

public:
	ComplexPlaneLayer(sf::RenderWindow* win);
	void respond(sf::Event event);
	void try_drag();

	void draw();
	void draw_complex_plane();
	void draw_gaussian_primes();

	void generate_gaussian_primes(int magnitude);
	void generate_primes();
};