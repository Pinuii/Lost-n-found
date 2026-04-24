#include "Button.h"
#include <iostream>
#pragma once

class plusXCarreParams : public Params {
public:
    plusXCarreParams() = default;
    plusXCarreParams(sf::RenderWindow* Window) {
        InternWindow = Window;
    }
    sf::RenderWindow* InternWindow;
};

class PlusXCarre : public Button {
private:
    sf::Texture _tableTexture;
public:
    PlusXCarre() = default;
    PlusXCarre(float width, float height, float x, float y);

    void setTextureTable(float x, float y);
    void onClick(Params* _params) override;
};