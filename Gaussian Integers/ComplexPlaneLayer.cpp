#include "ComplexPlaneLayer.h"

ComplexPlaneLayer::ComplexPlaneLayer(sf::RenderWindow* win) {
	ViewLayer::win = win;
	ViewLayer::view = win->getDefaultView();
	generate_primes();
	generate_gaussian_primes(AMOUNT);
}

void ComplexPlaneLayer::respond(sf::Event event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::C)
			anchor = sf::Vector2f(-4, 3) * zoom;
		if (event.key.code == sf::Keyboard::Num1 && last_magnitude != 100) {
			gaussian_primes.clear();
			generate_gaussian_primes(100);
		}
		if (event.key.code == sf::Keyboard::Num2 && last_magnitude != 1000) {
			gaussian_primes.clear();
			generate_gaussian_primes(1000);
		}
		if (event.key.code == sf::Keyboard::Num3 && last_magnitude != 4000) {
			gaussian_primes.clear();
			generate_gaussian_primes(4000);
		}
	}

	if (event.type == sf::Event::MouseWheelScrolled) {
		// Before we zoom, we reposition the anchor to the center then offset.
		anchor.x += 4 * zoom;
		anchor.y -= 3 * zoom;

		float old_zoom = zoom;
		zoom -= floor(event.mouseWheelScroll.delta)*zoom_tick * zoom;

		if (zoom > zoom_max)
			zoom = old_zoom;
		if (zoom < zoom_min)
			zoom = old_zoom;
		
		// Offset occurs here
		anchor.x -= 4 * zoom;
		anchor.y += 3 * zoom;

	}

	if (event.type == sf::Event::MouseButtonPressed)
		drag = true;
	if (event.type == sf::Event::MouseButtonReleased) {
		drag = false;
		last_mouse = sf::Vector2i(-1, -1);
	}
	try_drag();
}

void ComplexPlaneLayer::try_drag() {
	if (drag) {
		this_mouse = sf::Mouse::getPosition();
		if (last_mouse == sf::Vector2i(-1, -1))
			last_mouse = sf::Mouse::getPosition();
		sf::Vector2f diff = sf::Vector2f(this_mouse - last_mouse);
		diff.y = -diff.y;
		diff *= zoom;
		diff /= float(factor)*drag_factor;
		anchor -= diff;
		last_mouse = this_mouse;
	}
}

void ComplexPlaneLayer::draw() {
	draw_complex_plane();
	draw_gaussian_primes();
}

void ComplexPlaneLayer::draw_complex_plane() {

	// Capture the x-value of the anchor
	// Determine the amount of lattice lines to the left of the anchor.
	/*	This can be done by realizing 32px -> 1 unit and there are 1024px left of the anchor.
	Thus, there are 32 units left of the anchor point and 32 lines we should draw left.
	*/
	// Ceil the x-value to an integer.
	// REPEAT SUFFICIENT AMOUNT OF TIMES
	// Draw a line based on x value
	// Increase

	float x_marker = ceil(anchor.x/zoom) * zoom;
	for (int i = 0; i < 8; ++i) {
		float x_coord = (x_marker - anchor.x) * factor / zoom;
		if (abs(x_marker) <= 0.001) {
			vlines[2 * i] = sf::Vertex(sf::Vector2f(x_coord, 0), sf::Color::Blue);
			vlines[2 * i + 1] = sf::Vertex(sf::Vector2f(x_coord, 768), sf::Color::Blue);
		}
		else {
			vlines[2 * i] = sf::Vertex(sf::Vector2f(x_coord, 0), sf::Color(220, 220, 220, 127));
			vlines[2 * i + 1] = sf::Vertex(sf::Vector2f(x_coord, 768), sf::Color(220, 220, 220, 127));
		}
		x_marker += zoom;
	}

	float y_marker = floor(anchor.y/zoom) * zoom;
	for (int i = 0; i < 6; ++i) {
		float y_coord = (anchor.y - y_marker) * factor / zoom;
		if (abs(y_marker) <= 0.001) {
			hlines[2 * i] = sf::Vertex(sf::Vector2f(0, y_coord), sf::Color::Red);
			hlines[2 * i + 1] = sf::Vertex(sf::Vector2f(1024, y_coord), sf::Color::Red);
		}
		else {
			hlines[2 * i] = sf::Vertex(sf::Vector2f(0, y_coord), sf::Color(220, 220, 220, 127));
			hlines[2 * i + 1] = sf::Vertex(sf::Vector2f(1024, y_coord), sf::Color(220, 220, 220, 127));
		}
		y_marker -= zoom;
	}

	win->draw(vlines, 18, sf::Lines);
	win->draw(hlines, 14, sf::Lines);
}

void ComplexPlaneLayer::draw_gaussian_primes() {
	for (sf::Vector2i gaussian_prime : gaussian_primes) {
		if (gaussian_prime.x > ceil(anchor.x) + 8 * zoom || gaussian_prime.x < floor(anchor.x)) continue;
		if (gaussian_prime.y < floor(anchor.y) - 6 * zoom || gaussian_prime.y > ceil(anchor.y)) continue;

		sf::Vector2f diff = sf::Vector2f(gaussian_prime) - anchor;
		diff.y = -diff.y;
		diff *= (float(factor) / zoom);
		sf::RectangleShape dot;
		if (zoom < 1) {
			dot = sf::RectangleShape(sf::Vector2f(8, 8) / (zoom*zoom));
			diff.x -= 4 / (zoom*zoom);
			diff.y -= 4 / (zoom*zoom);
		} else {
			dot = sf::RectangleShape(sf::Vector2f(8, 8) / sqrt(zoom));
			diff.x -= 4 / sqrt(zoom);
			diff.y -= 4 / sqrt(zoom);
		}
		dot.setPosition(diff);
		dot.setFillColor(sf::Color::Yellow);
		dot.setOutlineColor(sf::Color::White);
		dot.setOutlineThickness(1);
		win->draw(dot);
	}
}

void ComplexPlaneLayer::generate_primes() {
	primes[0] = false; primes[1] = false;
	for (int i = 2; i < AMOUNT; ++i) primes[i] = true;
	for (int i = 2; i < AMOUNT; ++i) {
		if (primes[i]) {
			for (int j = 2 * i; j < AMOUNT; j += i) {
				primes[j] = false;
			}
		}
	}
}

void ComplexPlaneLayer::generate_gaussian_primes(int magnitude) {
	int x_start = -50;
	int x_end = 50;
	
	int y_start = 50;
	int y_end = -50;

	if (abs(x_start) >= AMOUNT || abs(x_end) >= AMOUNT || abs(y_start) >= AMOUNT || abs(y_end) >= AMOUNT) return;

	for (int a = x_start; a <= x_end; ++a) {
		for (int b = y_start; b >= y_end; --b) {
			if (a*b == 0 && (primes[abs(a)] || primes[abs(b)])) {
				if((abs(a + b)) % 4 == 3 && abs(a+b) <= magnitude) gaussian_primes.push_back(sf::Vector2i(a, b));
			} else if (a*a + b*b < AMOUNT && a*a + b*b <= magnitude) {
				if (primes[a*a + b*b]) {
					gaussian_primes.push_back(sf::Vector2i(a, b));
				}
			}
		}
	}
}
