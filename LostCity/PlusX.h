#include "Button.h"
#include <iostream>
#pragma once

class plusXParams : public Params {
public:
    plusXParams() = default;
    plusXParams(sf::RenderWindow* Window) {
        InternWindow = Window;
    }
    sf::RenderWindow* InternWindow;
};

class PlusX : public Button {
private:
    sf::Texture _tableTexture;
public:
    PlusX() = default;
    PlusX(float width, float height, float x, float y);

    void setTextureTable(float x, float y);
    void onClick(Params* _params) override;
};