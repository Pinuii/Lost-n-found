#include "Button.h"
#include <iostream>
#pragma once

class moinsXCarreParams : public Params {
public:
    moinsXCarreParams() = default;
    moinsXCarreParams(sf::RenderWindow* Window) {
        InternWindow = Window;
    }
    sf::RenderWindow* InternWindow;
};

class MoinsXCarre : public Button {
private:
    sf::Texture _tableTexture;
public:
    MoinsXCarre() = default;
    MoinsXCarre(float width, float height, float x, float y);

    void setTextureTable(float x, float y);
    void onClick(Params* _params) override;
};