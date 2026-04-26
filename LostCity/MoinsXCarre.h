#include "Button.h"
#include <iostream>
#pragma once

class moinsXCarreParams : public Params {
public:
	moinsXCarreParams() = default;
	GameManager* gm;
	sf::RenderWindow* InternWindow;
	moinsXCarreParams(sf::RenderWindow* w, GameManager* g)
		: InternWindow(w), gm(g) {
	}
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