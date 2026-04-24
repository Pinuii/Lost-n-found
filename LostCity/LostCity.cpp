#include <SFML/Graphics.hpp>
#include "graph.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Courbe");

	sf::VertexArray curve;

	Graph graph; // Add this line to declare the graph object

	graph.buildCurve();

	sf::Texture background;
	
	background.loadFromFile("assets/background.png");
	sf::View view(sf::FloatRect({ 0.f, 0.f }, { 800.f, 600.f }));
	float speed = 600.f;

	sf::Clock clock;

	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds();
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z))
			view.move({ 0.f, -speed * dt });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			view.move({ 0.f, speed * dt });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
			view.move({ -speed * dt, 0.f });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			view.move({ speed * dt, 0.f });

		window.clear(sf::Color::Magenta);
	sf::Sprite backgroundSprite(background);

		window.setView(view);

		window.draw(backgroundSprite);
		graph.draw(window);

		window.display();
	}
}
