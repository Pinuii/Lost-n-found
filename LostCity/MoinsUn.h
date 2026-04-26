#include "Button.h"
#include <iostream>
#pragma once

class moinsUnParams : public Params {
public:
	moinsUnParams() = default;
	GameManager* gm;
	sf::RenderWindow* InternWindow;
	moinsUnParams(sf::RenderWindow* w, GameManager* g)
		: InternWindow(w), gm(g) {
	}
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