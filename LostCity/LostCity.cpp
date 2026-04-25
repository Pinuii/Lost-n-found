#include <SFML/Graphics.hpp>
#include <algorithm>
#include <optional>
#include "Menu.h"
#include "Credits.h"

#include "Table.h"
#include "MoinsUn.h"
#include "MoinsDix.h"
#include "PlusUn.h"
#include "PlusDix.h"
#include "MoinsX.h"
#include "PlusX.h"
#include "PlusXCarre.h"
#include "MoinsXCarre.h"
#include "playBtn.h"
#include "graph.h"
#include "GameManager.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML works!");

	sf::VertexArray curve;
	sf::Font font;
	if (!font.openFromFile("font/mettre la bonne font.ttc"))
		return 1;

	Graph graph;
	GameManager gm(font);
	graph.buildCurve(font);

	sf::Texture background;
	sf::Texture tabletTexture;
	background.loadFromFile("assets/background.png");
	tabletTexture.loadFromFile("assets/tablet.png");

	Menu menu(font);

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

	MoinsDix* rect1 = new MoinsDix(50, 50, 0.f, 800);
	PlusDix* rect2 = new PlusDix(50, 50, 100.f, 810);
	MoinsUn* rect3 = new MoinsUn(50, 50, 200, 800);
	PlusUn* rect4 = new PlusUn(50, 50, 300, 810);
	MoinsX* rect5 = new MoinsX(50, 50, 400, 800);
	PlusX* rect6 = new PlusX(50, 50, 500, 810);
	MoinsXCarre* rect7 = new MoinsXCarre(50, 50, 600, 800);
	PlusXCarre* rect8 = new PlusXCarre(50, 50, 700.f, 810);
	PlayBtn* playButton = new PlayBtn(50, 50, 800.f, 800.f);

	rect1->setSize(60, 50);
	rect2->setSize(60, 50);
	rect3->setSize(60, 50);
	rect4->setSize(60, 50);
	rect5->setSize(60, 50);
	rect6->setSize(60, 50);
	rect7->setSize(60, 50);
	rect8->setSize(60, 50);
	playButton->setSize(300, 200);

	sf::Clock clock;
	sf::Sprite backgroundSprite(background);
	backgroundSprite.setScale(scale);
	backgroundSprite.setPosition({ 0.f, 0.f });

	sf::Sprite tabletSprite(tabletTexture);
	tabletSprite.setScale({ 15.5f, 15.5f });
	tabletSprite.setPosition({ 120.f, 480.f });

	bool gameRunning = false;
	playBtnParams playParams(&window);
	bool showCredits = false;

	Credits credits(font);

	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds();

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();

			if (!gameRunning) {
				const sf::Event::MouseButtonPressed* mouseEvent = event->getIf<sf::Event::MouseButtonPressed>();
				if (mouseEvent) {
					playButton->onClick(&playParams);
					gameRunning = true;
				}
			}
			else {
				const sf::Event::MouseButtonPressed* currentInputMouse = event->getIf<sf::Event::MouseButtonPressed>();
			}
		}

		if (!gameRunning) {
			menu.update(dt);
			window.clear();
			menu.draw(window);
			playButton->drawButton(window);
			window.display();
			continue;
		}

		if (gm.getScore() >= 5 && !showCredits) {
			showCredits = true;
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

		window.draw(backgroundSprite);
		window.draw(tabletSprite);
		rect1->drawButton(window);
		rect2->drawButton(window);
		rect3->drawButton(window);
		rect4->drawButton(window);
		rect5->drawButton(window);
		rect6->drawButton(window);
		rect7->drawButton(window);
		rect8->drawButton(window);
		gm.getTablet().draw(window);
		gm.getGraph().draw(window, font);
		window.display();
	}

	delete rect1; delete rect2; delete rect3; delete rect4;
	delete rect5; delete rect6; delete rect7; delete rect8;
	delete playButton;
	return 0;
}