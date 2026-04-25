#include "TabletCurve.h"
#include <limits>
#include <cmath>

TabletCurve::TabletCurve()
    : rng_(std::random_device{}()),
    curve_(sf::PrimitiveType::LineStrip)
{
    randomize();
}

void TabletCurve::randomize()
{
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

    float yMin = std::numeric_limits<float>::max();
    float yMax = std::numeric_limits<float>::lowest();
    for (float x = xMin; x <= xMax; x += 0.1f) {
        float y = generateFunction(x);
        yMin = std::min(yMin, y);
        yMax = std::max(yMax, y);
    }

    float rangeY = yMax - yMin;
    if (rangeY < 1.f) rangeY = 1.f;


    float marginX = (xMax - xMin) * 0.10f;
    float marginY = rangeY * 0.10f;

    float domainX = (xMax - xMin) + 2.f * marginX;
    float domainY = rangeY + 2.f * marginY;

    float scaleX = INNER_W / domainX;
    float scaleY = INNER_H / domainY;
    float scale = std::min(scaleX, scaleY); 

    float usedW = (xMax - xMin + 2.f * marginX) * scale;
    float usedH = (rangeY + 2.f * marginY) * scale;

    float originX = INNER_X + (INNER_W - usedW) / 2.f + (0.f - xMin) * scale;
    float originY = INNER_Y + (INNER_H - usedH) / 2.f + (yMax + marginY) * scale;

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