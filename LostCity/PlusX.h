#include "Button.h"
#include <iostream>
#pragma once

class plusXParams : public Params {
public:
	plusXParams() = default;
	GameManager* gm;
	sf::RenderWindow* InternWindow;
	plusXParams(sf::RenderWindow* w, GameManager* g)
		: InternWindow(w), gm(g) {
	}
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