#include "TabletCurve.h"
#include <limits>
#include <cmath>
#include <iostream>

TabletCurve::TabletCurve()
    : rng_(std::random_device{}()),
    curve_(sf::PrimitiveType::LineStrip)
{
    randomize();
    if (!buffer.loadFromFile("assets/sound/stone.wav"))
        std::cout << "Failed to load sound stone\n";
}

void TabletCurve::randomize()
{
    sound.play();
    std::uniform_int_distribution<int> distAB(-3, 3);
    std::uniform_int_distribution<int> distC(-5, 5);
    do { a_ = distAB(rng_); } while (a_ == 0);
    b_ = distAB(rng_);
    c_ = distC(rng_);
}

float TabletCurve::generateFunction(float x) const
{
    return float(a_) * x * x + float(b_) * x + float(c_);
}

void TabletCurve::buildCurve()
{
    curve_.clear();

    const float MARGIN_PX = 30.f;
    float zoneX0 = INNER_X + MARGIN_PX;
    float zoneY0 = INNER_Y + MARGIN_PX;
    float zoneW = INNER_W - 2.f * MARGIN_PX;
    float zoneH = INNER_H - 2.f * MARGIN_PX;

    float scale = 30.f;
    float originX = zoneX0 + zoneW / 2.f;
    float originY = zoneY0 + zoneH / 2.f;

    float xMin = -(zoneW / 2.f) / scale;
    float xMax = (zoneW / 2.f) / scale;
    float yMin = -(zoneH / 2.f) / scale;
    float yMax = (zoneH / 2.f) / scale;

    originX_ = originX;
    originY_ = originY;
    scale_ = scale;
    xMin_ = xMin;
    xMax_ = xMax;
    yMin_ = yMin;
    yMax_ = yMax;

    for (float x = xMin; x <= xMax; x += 0.05f) {
        float y = generateFunction(x);
        sf::Vertex v;
        v.position = { originX + x * scale, originY - y * scale };
        v.color = sf::Color(210, 190, 140);
        curve_.append(v);
    }
}

void TabletCurve::draw(sf::RenderWindow& window, const sf::View& gameView) const
{
    sf::View previousView = window.getView();
    std::cout << "a: " << a_ << ", b: " << b_ << ", c: " << c_ << std::endl;
    // View clippée aux coordonnées monde de la tablette
    sf::View clipView(sf::FloatRect(
        { INNER_X, INNER_Y },
        { INNER_W, INNER_H }
    ));


    sf::Vector2f topLeft = static_cast<sf::Vector2f>(window.mapCoordsToPixel({ INNER_X, INNER_Y }, gameView));
    sf::Vector2f botRight = static_cast<sf::Vector2f>(window.mapCoordsToPixel({ INNER_X + INNER_W, INNER_Y + INNER_H }, gameView));
    sf::Vector2u winSize = window.getSize();

    clipView.setViewport(sf::FloatRect(
        { topLeft.x / winSize.x, topLeft.y / winSize.y },
        { (botRight.x - topLeft.x) / winSize.x, (botRight.y - topLeft.y) / winSize.y }
    ));

    window.setView(clipView);

    // Axes
    sf::VertexArray axes(sf::PrimitiveType::Lines, 4);
    axes[0].position = { originX_ + xMin_ * scale_, originY_ };
    axes[0].color = sf::Color(80, 60, 30);
    axes[1].position = { originX_ + xMax_ * scale_, originY_ };
    axes[1].color = sf::Color(80, 60, 30);
    axes[2].position = { originX_, originY_ - yMax_ * scale_ };
    axes[2].color = sf::Color(80, 60, 30);
    axes[3].position = { originX_, originY_ - yMin_ * scale_ };
    axes[3].color = sf::Color(80, 60, 30);
    window.draw(axes);

    // Graduations
    sf::VertexArray ticks(sf::PrimitiveType::Lines);
    const float tickSize = 4.f;

    for (int i = (int)std::ceil(xMin_); i <= (int)std::floor(xMax_); ++i) {
        if (i == 0) continue;
        float sx = originX_ + i * scale_;
        sf::Vertex v1, v2;
        v1.position = { sx, originY_ - tickSize }; v1.color = sf::Color(80, 60, 30);
        v2.position = { sx, originY_ + tickSize }; v2.color = sf::Color(80, 60, 30);
        ticks.append(v1); ticks.append(v2);
    }

    for (int j = (int)std::ceil(yMin_); j <= (int)std::floor(yMax_); ++j) {
        if (j == 0) continue;
        float sy = originY_ - j * scale_;
        sf::Vertex v1, v2;
        v1.position = { originX_ - tickSize, sy }; v1.color = sf::Color(80, 60, 30);
        v2.position = { originX_ + tickSize, sy }; v2.color = sf::Color(80, 60, 30);
        ticks.append(v1); ticks.append(v2);
    }

    window.draw(ticks);
    window.draw(curve_);

    window.setView(previousView);
}