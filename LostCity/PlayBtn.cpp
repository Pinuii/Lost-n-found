#include "playBtn.h"

PlayBtn::PlayBtn(float width, float height, float x, float y)
    : Button(width, height, x, y)
{
    _button = sf::RectangleShape({ 2000.f, 1000.f });
    _tableTexture = sf::Texture();
    _tableTexture.loadFromFile("assets/play.png");
    _button.setTexture(&_tableTexture);
    setPosition(x, y);
}

void PlayBtn::setTextureTable(float x, float y)
{
    _button.setTextureRect({ {10, 10}, {50, 30} });
}

void PlayBtn::onClick(Params* _params)
{
}