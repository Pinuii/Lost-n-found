#include "MoinsXCarre.h"

MoinsXCarre::MoinsXCarre(float width, float height, float x, float y)
    : Button(width, height, x, y)
{
    _button = sf::RectangleShape({ 2000.f, 1000.f });
    _tableTexture = sf::Texture();
    _tableTexture.loadFromFile("assets/minusXsquare.png");
    _button.setTexture(&_tableTexture);
    setPosition(x, y);
}

void MoinsXCarre::setTextureTable(float x, float y)
{
    _button.setTextureRect({ {10, 10}, {50, 30} });
}

void MoinsXCarre::onClick(Params* _params)
{
    moinsXCarreParams* p = static_cast<moinsXCarreParams*>(_params);
    if (p && p->gm)
    {
        p->gm->getGraph().incrementA(-1);
        p->gm->onButtonPressed();
    }
}