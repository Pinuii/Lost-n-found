#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "SFML works!");
	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
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

		// Appliquer la vue
		window.setView(view);

		window.clear();
		sf::Sprite backgroundSprite(background);
		window.draw(backgroundSprite);
		//window.draw(shape);
		window.display();
	}
}
