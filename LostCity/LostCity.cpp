#include <SFML/Graphics.hpp>
#include <algorithm>

#include "Table.h"
#include "MoinsUn.h"
#include "MoinsDix.h"
#include "PlusUn.h"
#include "PlusDix.h"
#include "MoinsX.h"
#include "PlusX.h"
#include "PlusXCarre.h"
#include "MoinsXCarre.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML works!");
	sf::Texture background;
	background.loadFromFile("assets/background.png");
	sf::View view(sf::FloatRect({ 0.f, 450.f }, { 800.f, 600.f }));
	float speed = 600.f;
	
	sf::Vector2f center = static_cast<sf::Vector2f>(view.getCenter());
	sf::Vector2f size = static_cast<sf::Vector2f>(view.getSize());
	sf::Vector2f scale = { 1.9f, 1.9f };
	sf::Vector2f backgroundSize = { size.x * scale.x, size.y * scale.y };

	sf::Vector2f viewSize = view.getSize();
	sf::Vector2f textureSize = static_cast<sf::Vector2f>(background.getSize());

	moinsDixParams moinsDixParams(&window);
	plusDixParams plusDixParams(&window);
	moinsUnParams moinsUnParams(&window);
	plusUnParams plusUnParams(&window);
	moinsXParams moinsXParams(&window);
	plusXParams plusXParams(&window);
	moinsXCarreParams moinsXCarreParams(&window);
	plusXCarreParams plusXCarreParams(&window);


	MoinsDix* rect1 = new MoinsDix(1440.f, 900.f, 700.f, 450.f);
	PlusDix* rect2 = new PlusDix(1440.f, 900.f, 700.f, 450.f);
	MoinsUn* rect3 = new MoinsUn(1440.f, 900.f, 700.f, 450.f);
	PlusUn* rect4 = new PlusUn(1440.f, 900.f, 700.f, 450.f);
	MoinsX* rect5 = new MoinsX(1440.f, 900.f, 700.f, 450.f);
	PlusX* rect6 = new PlusX(1440.f, 900.f, 700.f, 450.f);
	MoinsXCarre* rect7 = new MoinsXCarre(1440.f, 900.f, 700.f, 450.f);
	PlusXCarre* rect8 = new PlusXCarre(1440.f, 900.f, 700.f, 450.f);

	sf::Clock clock;

	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds();

		while (const std::optional event = window.pollEvent())
		{
			const sf::Event::MouseButtonPressed* currentInputMouse = event->getIf<sf::Event::MouseButtonPressed>();

			if (event->is<sf::Event::Closed>())
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
			view.move({ -speed * dt, 0.f });
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			view.move({ speed * dt, 0.f });

		sf::Vector2f targetCenter = view.getCenter();

		targetCenter.x = std::max(viewSize.x * 0.5f,
						 std::min(targetCenter.x, backgroundSize.x - viewSize.x * 0.6f));

		view.setCenter(targetCenter);
		window.setView(view);

		window.clear();

		sf::Sprite backgroundSprite(background);
		backgroundSprite.setScale(scale);
		backgroundSprite.setPosition({ 0.f, 0.f });

		window.draw(backgroundSprite);
		rect1->drawButton(window);
		rect2->drawButton(window);
		rect3->drawButton(window);
		rect4->drawButton(window);
		rect5->drawButton(window);
		rect6->drawButton(window);
		rect7->drawButton(window);
		rect8->drawButton(window);

		window.display();
	}
}
