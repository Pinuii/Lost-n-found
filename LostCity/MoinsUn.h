#include "Button.h"
#include <iostream>
#pragma once

class moinsUnParams : public Params {
public:
    moinsUnParams() = default;
    moinsUnParams(sf::RenderWindow* Window) {
        InternWindow = Window;
    }
    sf::RenderWindow* InternWindow;
};

class MoinsUn : public Button {
private:
    sf::Texture _tableTexture;
public:
    MoinsUn() = default;
    MoinsUn(float width, float height, float x, float y);

    void setTextureTable(float x, float y);
    void onClick(Params* _params) override;
};