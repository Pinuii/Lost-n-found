#include "Button.h"
#include <iostream>
#pragma once

class moinsDixParams : public Params {
public:
    moinsDixParams() = default;
    moinsDixParams(sf::RenderWindow* Window) {
        InternWindow = Window;
    }
    sf::RenderWindow* InternWindow;
};

class MoinsDix : public Button {
private:
    sf::Texture _tableTexture;
public:
    MoinsDix() = default;
    MoinsDix(float width, float height, float x, float y);

    void setTextureTable(float x, float y);
    void onClick(Params* _params) override;
};