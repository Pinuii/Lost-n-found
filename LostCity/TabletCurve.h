#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <iostream>

class TabletCurve
{
public:
    TabletCurve();
    void randomize();
    void buildCurve();
    void draw(sf::RenderWindow& window, const sf::View& gameView) const;
    int getA() const { return a_; }
    int getB() const { return b_; }
    int getC() const { return c_; }
	

private:
    int a_ = 1, b_ = 0, c_ = 0;
    std::mt19937 rng_;
    sf::VertexArray curve_;
    sf::SoundBuffer buffer;
    sf::Sound sound{ buffer };

    static constexpr float INNER_X = 180.f;
    static constexpr float INNER_Y = 530.f;
    static constexpr float INNER_W = 326.f;
    static constexpr float INNER_H = 356.f;

    float originX_ = 0.f;
    float originY_ = 0.f;
    float scale_ = 1.f;
    float xMin_ = -5.f, xMax_ = 5.f;
    float yMin_ = -5.f, yMax_ = 5.f;

    float generateFunction(float x) const;
};