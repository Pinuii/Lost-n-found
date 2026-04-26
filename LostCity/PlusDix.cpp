#include "PlusDix.h"

PlusDix::PlusDix(float width, float height, float x, float y)
    : Button(width, height, x, y)
{
    _button = sf::RectangleShape({ 2000.f, 1000.f });
    _tableTexture = sf::Texture();
    _tableTexture.loadFromFile("assets/plusTen.png");
    _button.setTexture(&_tableTexture);
    setPosition(x, y);
}

void PlusDix::setTextureTable(float x, float y)
{
    _button.setTextureRect({ {10, 10}, {50, 30} });
}

void PlusDix::onClick(Params* _params)
{
    plusDixParams* p = static_cast<plusDixParams*>(_params);
    if (p && p->gm)
    {
        p->gm->getGraph().incrementC(10);
        p->gm->onButtonPressed();
    }
}