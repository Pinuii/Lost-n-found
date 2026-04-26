#include "Button.h"
#include <iostream>
#pragma once

class plusXCarreParams : public Params {
public:
	plusXCarreParams() = default;
	GameManager* gm;
	sf::RenderWindow* InternWindow;
	plusXCarreParams(sf::RenderWindow* w, GameManager* g)
		: InternWindow(w), gm(g) {
	}
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