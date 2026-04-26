#include "Button.h"
#include <iostream>
#pragma once

class moinsDixParams : public Params {
public:
    sf::RenderWindow* InternWindow;
    GameManager* gm;
    moinsDixParams(sf::RenderWindow* w, GameManager* g)
        : InternWindow(w), gm(g) {
    }
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