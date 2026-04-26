#include "Button.h"
#include <iostream>
#pragma once

class plusDixParams : public Params {
public:
	plusDixParams() = default;
	GameManager* gm;
	sf::RenderWindow* InternWindow;
	plusDixParams(sf::RenderWindow* w, GameManager* g)
		: InternWindow(w), gm(g) {
	}
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