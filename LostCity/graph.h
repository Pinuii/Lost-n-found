#pragma once
#include <random>
#include <SFML/Graphics.hpp>

class Graph
{
public:
	Graph();

	void buildCurve();
	void draw(sf::RenderWindow& window);

private:
	float generateFunction(float x);


	float a, b, c;

	std::mt19937 rng;

	sf::VertexArray curve;

	float offsetX = 400.f;
	float offsetY = 300.f;
};