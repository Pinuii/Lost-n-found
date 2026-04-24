#include "Button.h"
#include <iostream>
#pragma once

class plusDixParams : public Params {
public:
    plusDixParams() = default;
    plusDixParams(sf::RenderWindow* Window) {
        InternWindow = Window;
    }
    sf::RenderWindow* InternWindow;
};

class PlusDix : public Button {
private:
    sf::Texture _tableTexture;
public:
    PlusDix() = default;
    PlusDix(float width, float height, float x, float y);

    void setTextureTable(float x, float y);
    void onClick(Params* _params) override;
};