#include "graph.h"

Graph::Graph()
	: rng(std::random_device{}()), curve(sf::PrimitiveType::LineStrip)
{
	std::uniform_int_distribution<int> dist(-10, 10);
	std::uniform_int_distribution<int> distC(-99, 99);

	a = dist(rng);
	b = dist(rng);
	c = distC(rng);
}

float Graph::generateFunction(float x)
{
	return a * x * x + b * x + c;
}

void Graph::buildCurve()
{
	curve.clear();

	float scale = 20.f;

	float minY = std::numeric_limits<float>::max();
	float maxY = std::numeric_limits<float>::lowest();

	for (float x = -10.f; x <= 10.f; x += 0.05f)
	{
		float y = generateFunction(x);
		minY = std::min(minY, y);
		maxY = std::max(maxY, y);
	}

	float rangeY = maxY - minY;

	if (rangeY == 0) rangeY = 1; // éviter division par 0

	float scaleY = 500.f / rangeY; // 500 = hauteur écran approx
	float scaleX = 40.f; // tu peux ajuster
	float centerY = (maxY + minY) / 2.f;

	for (float x = -10.f; x <= 10.f; x += 0.05f)
	{
		float y = generateFunction(x);

		float screenX = offsetX + x * scale;
		float screenY = offsetY - (y - centerY) * scaleY;

		sf::Vertex vertex;

		vertex.position = sf::Vector2f(screenX, screenY);
		vertex.color = sf::Color::Black;
		curve.append(vertex);
	}
	/*for (float x = -10.f; x <= 10.f; x += 0.05f)
{
	float y = generateFunction(x);

	float screenX = offsetX + x * scaleX;
	float screenY = offsetY - (y - centerY) * scaleY;

	curve.append(sf::Vertex(
		sf::Vector2f(screenX, screenY),
		sf::Color::Black
	));
}*/

}

void Graph::draw(sf::RenderWindow& window)
{
	window.draw(curve);
}