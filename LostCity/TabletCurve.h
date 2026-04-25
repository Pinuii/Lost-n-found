#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
	sf::SoundBuffer buffer;
	sf::Sound sound{buffer}; // Initialize with buffer

	float INNER_X = 180.f;
	static constexpr float INNER_Y = 530.f;
	static constexpr float INNER_W = 396.f; 
	static constexpr float INNER_H = 396.f;

	float generateFunction(float x) const;
};