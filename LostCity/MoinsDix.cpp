#include "MoinsDix.h"

MoinsDix::MoinsDix(float width, float height, float x, float y)
    : Button(width, height, x, y)
{
    _button = sf::RectangleShape({ 2000.f, 1000.f });
    _tableTexture = sf::Texture();
    _tableTexture.loadFromFile("assets/minusTen.png");
    _button.setTexture(&_tableTexture);
    setPosition(x, y);
}

void MoinsDix::setTextureTable(float x, float y)
{
    _button.setTextureRect({ {10, 10}, {50, 30} });
}

void MoinsDix::onClick(Params* _params)
{
    moinsDixParams* p = static_cast<moinsDixParams*>(_params);
    if (p && p->gm)
    {
        p->gm->getGraph().incrementC(-10);
        p->gm->onButtonPressed();
    }
}