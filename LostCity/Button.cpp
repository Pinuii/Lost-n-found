#include "Button.h"
#include <iostream>

Button::Button(float width, float height, float x, float y) {
    _button = sf::RectangleShape({ width, height });
    setPosition(x - width / 2.f, y - height / 2.f);
}

sf::Vector2f Button::getPosition() {
    return _button.getPosition();
}

sf::Vector2f Button::getButtonExtent() {
    return getPosition() + _button.getSize();
}

void Button::setSize(float x, float y) {
    _button.setSize({ x, y });
}

void Button::setPosition(float x, float y) {
    _button.setPosition({ x, y });
}

void Button::setColor(const sf::Color& color) {
    _button.setFillColor(color);
}

void Button::drawButton(sf::RenderWindow& window) {
    window.draw(_button);
}

bool Button::detectOnClick(const sf::Event::MouseButtonPressed* currentInputMouse, sf::RenderWindow& window) {
    if (!currentInputMouse) return false;

    sf::Vector2i pixelPos(currentInputMouse->position.x, currentInputMouse->position.y);
    sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

    return _button.getGlobalBounds().contains(worldPos);
}

void Button::onClick(Params* _params) {}
