#include "Button.h"
#include <iostream>
#pragma once

class playBtnParams : public Params {
public:
    playBtnParams() = default;
    playBtnParams(sf::RenderWindow* Window, GameManager* gm = nullptr) {
        InternWindow = Window;
        this->gm = gm;
    }
    sf::RenderWindow* InternWindow = nullptr;
    GameManager* gm = nullptr;
};

class PlayBtn : public Button {
private:
    sf::Texture _tableTexture;
public:
    PlayBtn() = default;
    PlayBtn(float width, float height, float x, float y);

    void setTextureTable(float x, float y);
    void onClick(Params* _params) override;
};