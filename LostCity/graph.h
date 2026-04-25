#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include <limits>
#include <string>

class Graph
{
public:
    Graph();

    // Le joueur modifie sa fonction via ces méthodes
    void addA(int v) { a_ += v; }
    void addB(int v) { b_ += v; }
    void addC(int v) { c_ += v; }
    void resetPlayer() { a_ = 0; b_ = 0; c_ = 0; }

    int getA() const { return a_; }
    int getB() const { return b_; }
    int getC() const { return c_; }

    void buildCurve(sf::Font& font);
    void draw(sf::RenderWindow& window, sf::Font& font);

private:
    sf::Font* font_ = nullptr;

    int a_ = 0, b_ = 0, c_ = 0;

    // Plan de travail — à positionner où tu veux sur l'écran
    static constexpr float PAD_LEFT = 700.f;
    static constexpr float PAD_TOP = 480.f;
    static constexpr float TABLET_W = 500.f;
    static constexpr float TABLET_H = 500.f;
    static constexpr float MARGIN = 20.f;
    // Labels précalculés
    std::vector<sf::Text> labels_;

    float scale_ = 20.f;
    float originX_ = 0.f;
    float originY_ = 0.f;
    float xMin_ = -10.f, xMax_ = 10.f;
    float yMin_ = -10.f, yMax_ = 10.f;

    sf::VertexArray curve_;

    float       generateFunction(float x) const;
    std::string equation()        const;
    void        drawBackground(sf::RenderWindow& window);
    void        drawGrid(sf::RenderWindow& window);
    void        drawAxes(sf::RenderWindow& window);
};