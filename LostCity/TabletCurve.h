#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class TabletCurve
{
public:
	TabletCurve();
	void randomize();
	void buildCurve();
	void draw(sf::RenderWindow& window) const;

	int getA() const { return a_; }
	int getB() const { return b_; }
	int getC() const { return c_; }

private:
	int a_ = 1, b_ = 0, c_ = 0;
	std::mt19937 rng_;
	sf::VertexArray curve_;

	// Position et taille de la zone intérieure de la tablette sprite
	float INNER_X = 180.f;
	static constexpr float INNER_Y = 530.f;   // PAD_TOP(480)  + bordure(50)
	static constexpr float INNER_W = 396.f;   // 496 - 2*50
	static constexpr float INNER_H = 396.f;

	float generateFunction(float x) const;
};