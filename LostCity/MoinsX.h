#include "Button.h"
#include <iostream>
#pragma once

class moinsXParams : public Params {
public:
    moinsXParams() = default;
    moinsXParams(sf::RenderWindow* Window) {
        InternWindow = Window;
    }
    sf::RenderWindow* InternWindow;
};

class MoinsX : public Button {
private:
    sf::Texture _tableTexture;
public:
    MoinsX() = default;
    MoinsX(float width, float height, float x, float y);

    void setTextureTable(float x, float y);
    void onClick(Params* _params) override;
};