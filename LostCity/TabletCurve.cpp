#include "TabletCurve.h"
#include <limits>
#include <cmath>
#include <iostream>

TabletCurve::TabletCurve()
    : rng_(std::random_device{}()),
    curve_(sf::PrimitiveType::LineStrip)
{
    randomize();
    if (!buffer.loadFromFile("assets/sound/stone.wav")) {
		std::cout << "Failed to load sound stone \n";
	}
}

void TabletCurve::randomize()
{
//    sf::SoundBuffer buffer("stone.wav");
	sound.play();
    std::uniform_int_distribution<int> distAB(-3, 3);
    std::uniform_int_distribution<int> distC(-5, 5);
    std::uniform_real_distribution<float> distX(150.f, 180.f);
    do { a_ = distAB(rng_); } while (a_ == 0);
    b_ = distAB(rng_);
    c_ = distC(rng_);
	INNER_X = distX(rng_);
}

float TabletCurve::generateFunction(float x) const
{
    return float(a_) * x * x + float(b_) * x + float(c_);
}

void TabletCurve::buildCurve()
{
    curve_.clear();

    const float xMin = -5.f, xMax = 5.f;

    // 1. Vrai min/max Y sur l'intervalle, en incluant y=0 obligatoirement
    float yMin = 0.f;
    float yMax = 0.f;
    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = generateFunction(x);
        yMin = std::min(yMin, y);
        yMax = std::max(yMax, y);
    }

    // 2. Sécurité si tout est plat
    if (yMax - yMin < 1.f) { yMin -= 1.f; yMax += 1.f; }

    // 3. Zone utile = tablette moins 30px de marge partout
    const float MARGIN_PX = 30.f;
    float zoneX0 = INNER_X + MARGIN_PX;
    float zoneY0 = INNER_Y + MARGIN_PX;
    float zoneW = INNER_W - 2.f * MARGIN_PX;
    float zoneH = INNER_H - 2.f * MARGIN_PX;

    // 4. Échelle orthonormée
    float scaleX = zoneW / (xMax - xMin);
    float scaleY = zoneH / (yMax - yMin);
    float scale = std::min(scaleX, scaleY);

    // 5. Origine = position de (x=0, y=0) en pixels, centrée dans la zone
    float usedW = (xMax - xMin) * scale;
    float usedH = (yMax - yMin) * scale;

    float originX = zoneX0 + (zoneW - usedW) / 2.f + (0.f - xMin) * scale;
    float originY = zoneY0 + (zoneH - usedH) / 2.f + (yMax - 0.f) * scale;

    // 6. Dessin — impossible de sortir de la zone
    for (float x = xMin; x <= xMax; x += 0.05f) {
        float y = generateFunction(x);
        sf::Vertex v;
        v.position = { originX + x * scale, originY - y * scale };
        v.color = sf::Color(210, 190, 140);
        curve_.append(v);
    }
}

void TabletCurve::draw(sf::RenderWindow& window) const
{
    window.draw(curve_);
}