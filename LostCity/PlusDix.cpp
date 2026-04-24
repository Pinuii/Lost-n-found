#include "PlusDix.h"

PlusDix::PlusDix(float width, float height, float x, float y)
    : Button(width, height, x, y)
{
    _button = sf::RectangleShape({ 2000.f, 1000.f });
    _tableTexture = sf::Texture();
    _tableTexture.loadFromFile("assets/buttons_calculus.png");
    _button.setTexture(&_tableTexture);
    setPosition(x, y);
}

void PlusDix::setTextureTable(float x, float y)
{
    _button.setTextureRect({ {10, 10}, {50, 30} });
}

void PlusDix::onClick(Params* _params)
{
    plusDixParams* castedParams = static_cast<plusDixParams*>(_params);
    if (castedParams && castedParams->InternWindow) {
        castedParams->InternWindow->close();
    }
    std::cout << "Quit\n";
}