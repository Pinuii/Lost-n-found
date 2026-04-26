#include <SFML/Graphics.hpp>
#include "GameManager.h"
#pragma once

class Params {};

class Button {
public:
    sf::RectangleShape _button;

public:
    Button() = default;
    Button(float width, float height, float x, float y);

    sf::Vector2f getPosition();
    sf::Vector2f getButtonExtent();

    void setSize(float x, float y);
    void setPosition(float x, float y);
    void setColor(const sf::Color& color);
    void drawButton(sf::RenderWindow& window);

    bool detectOnClick(const sf::Event::MouseButtonPressed* currentInputMouse, sf::RenderWindow& window);

    virtual void onClick(Params* _params);
    bool isHovered(sf::Vector2f pos) const;
};