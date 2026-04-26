#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <limits>
#include <string>

class Graph
{
public:
    Graph();
    void incrementA(int delta);
    void incrementB(int delta);
    void incrementC(int delta);
    void resetPlayer() { a_ = 0; b_ = 0; c_ = 0; }
    int getA() const { return a_; }
    int getB() const { return b_; }
    int getC() const { return c_; }
    void buildCurve(sf::Font& font);
    void draw(sf::RenderWindow& window, sf::Font& font);

private:
    sf::Font* font_ = nullptr;
    int a_ = 0, b_ = 0, c_ = 0;

    static constexpr float PAD_LEFT = 700.f;
    static constexpr float PAD_TOP = 480.f;
    static constexpr float TABLET_W = 500.f;
    static constexpr float TABLET_H = 500.f;
    static constexpr float MARGIN = 20.f;

    std::vector<sf::Text> labels_;
    float scale_ = 20.f;
    float originX_ = 0.f;
    float originY_ = 0.f;
    float xMin_ = -10.f, xMax_ = 10.f;
    float yMin_ = -10.f, yMax_ = 10.f;

    sf::VertexArray curve_;

    float       generateFunction(float x) const;
    std::string equation()                const;
    void        drawBackground(sf::RenderWindow& window);
    void        drawGrid(sf::RenderWindow& window);
    void        drawAxes(sf::RenderWindow& window);
};