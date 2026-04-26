#include "PlusXCarre.h"

PlusXCarre::PlusXCarre(float width, float height, float x, float y)
    : Button(width, height, x, y)
{
    _button = sf::RectangleShape({ 2000.f, 1000.f });
    _tableTexture = sf::Texture();
    _tableTexture.loadFromFile("assets/plusXsquare.png");
    _button.setTexture(&_tableTexture);
    setPosition(x, y);
}

void PlusXCarre::setTextureTable(float x, float y)
{
    _button.setTextureRect({ {10, 10}, {50, 30} });
}

void PlusXCarre::onClick(Params* _params)
{
    plusXCarreParams* castedParams = static_cast<plusXCarreParams*>(_params);
    if (castedParams && castedParams->InternWindow) {
        castedParams->InternWindow->close();
    }
    std::cout << "Quit\n";
}