#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
#include "PlayBtn.h"
#include "graph.h"
#include "GameManager.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "SFML works!");

	sf::VertexArray curve;
	sf::Font font;
	if (!font.openFromFile("font/Roboto.ttf"))
		return 1;

	Graph graph;
	GameManager gm(font);
	graph.buildCurve(font);

	sf::Texture background;
	sf::Texture tabletTexture;
	background.loadFromFile("assets/background.png");
	tabletTexture.loadFromFile("assets/tablet.png");

	sf::Music music;
	if (!music.openFromFile("assets/music/chopin.ogg"))
		return -1;

	Menu menu(font);

	sf::View view(sf::FloatRect({ 0.f, 450.f }, { 800.f, 600.f }));
	float speed = 600.f;

	sf::Vector2f center = static_cast<sf::Vector2f>(view.getCenter());
	sf::Vector2f size = static_cast<sf::Vector2f>(view.getSize());
	sf::Vector2f scale = { 1.9f, 1.9f };
	sf::Vector2f backgroundSize = { size.x * scale.x, size.y * scale.y };

	sf::Vector2f viewSize = view.getSize();
	sf::Vector2f textureSize = static_cast<sf::Vector2f>(background.getSize());

	moinsDixParams moinsDixParams(&window, &gm);
	plusDixParams plusDixParams(&window, &gm);
	moinsUnParams moinsUnParams(&window, &gm);
	plusUnParams plusUnParams(&window, &gm);
	moinsXParams moinsXParams(&window, &gm);
	plusXParams plusXParams(&window, &gm);
	moinsXCarreParams moinsXCarreParams(&window, &gm);
	plusXCarreParams plusXCarreParams(&window, &gm);
	playBtnParams playParams(&window, &gm);

	MoinsDix* rect1 = new MoinsDix(30, 50, 1250, 550.f);
	PlusDix* rect2 = new PlusDix(30, 50, 1350, 560.f);
	MoinsUn* rect3 = new MoinsUn(30, 50, 1250, 600.f);
	PlusUn* rect4 = new PlusUn(30, 50, 1350, 610.f);
	MoinsX* rect5 = new MoinsX(30, 50, 1250, 650.f);
	PlusX* rect6 = new PlusX(30, 50, 1350, 660.f);
	MoinsXCarre* rect7 = new MoinsXCarre(30, 50, 1250, 710.f);
	PlusXCarre* rect8 = new PlusXCarre(30, 50, 1350, 720.f);
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

	music.setVolume(100.f);
	music.setLooping(true);
	music.play();

	bool gameRunning = false;
	bool showCredits = false;
	Credits credits(font);

	while (window.isOpen())
	{
		float dt = clock.restart().asSeconds();

		if (showCredits)
		{
			while (const std::optional event = window.pollEvent())
			{
				if (event->is<sf::Event::Closed>())
					window.close();

				const sf::Event::KeyPressed* keyEvent = event->getIf<sf::Event::KeyPressed>();
				if (keyEvent)
				{
					if (credits.handleKey(keyEvent->code))
						showCredits = false;
				}
			}

			sf::View defaultView = window.getDefaultView();
			window.setView(defaultView);
			credits.draw(window);
			window.display();
			continue;
		}

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
				const sf::Event::MouseButtonPressed* click = event->getIf<sf::Event::MouseButtonPressed>();
				if (click) {
					sf::Vector2f mousePos = window.mapPixelToCoords(
						{ (int)click->position.x, (int)click->position.y });

					if (rect1->isHovered(mousePos)) rect1->onClick(&moinsDixParams);
					if (rect2->isHovered(mousePos)) rect2->onClick(&plusDixParams);
					if (rect3->isHovered(mousePos)) rect3->onClick(&moinsUnParams);
					if (rect4->isHovered(mousePos)) rect4->onClick(&plusUnParams);
					if (rect5->isHovered(mousePos)) rect5->onClick(&moinsXParams);
					if (rect6->isHovered(mousePos)) rect6->onClick(&plusXParams);
					if (rect7->isHovered(mousePos)) rect7->onClick(&moinsXCarreParams);
					if (rect8->isHovered(mousePos)) rect8->onClick(&plusXCarreParams);
				}
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
			credits.show("Well Played you founded all 5 functions and the ancient city!");
			continue;
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
		gm.getTablet().draw(window, view);
		gm.getGraph().draw(window, font);

		sf::Text score(font, "Found : " + std::to_string(gm.getScore()) + " / 5", 20);
		score.setPosition({ 900.f, 460.f });
		window.draw(score);

		window.display();
	}

	delete rect1; delete rect2; delete rect3; delete rect4;
	delete rect5; delete rect6; delete rect7; delete rect8;
	delete playButton;

	return 0;
}