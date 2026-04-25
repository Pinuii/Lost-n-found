#include "Button.h"
#include <iostream>
#pragma once

class plusUnParams : public Params {
public:
    plusUnParams() = default;
    plusUnParams(sf::RenderWindow* Window) {
        InternWindow = Window;
    }
    sf::RenderWindow* InternWindow;
};

class PlusUn : public Button {
private:
    sf::Texture _tableTexture;
public:
    PlusUn() = default;
    PlusUn(float width, float height, float x, float y);

    void setTextureTable(float x, float y);
    void onClick(Params* _params) override;
};