#include "PlusX.h"

PlusX::PlusX(float width, float height, float x, float y)
    : Button(width, height, x, y)
{
    _button = sf::RectangleShape({ 2000.f, 1000.f });
    _tableTexture = sf::Texture();
    _tableTexture.loadFromFile("assets/plusX.png");
    _button.setTexture(&_tableTexture);
    setPosition(x, y);
}

void PlusX::setTextureTable(float x, float y)
{
    _button.setTextureRect({ {10, 10}, {50, 30} });
}

void PlusX::onClick(Params* _params)
{
    plusXParams* castedParams = static_cast<plusXParams*>(_params);
    if (castedParams && castedParams->InternWindow) {
        castedParams->InternWindow->close();
    }
    std::cout << "Quit\n";
}