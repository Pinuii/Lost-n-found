#include "graph.h"
#include <sstream>
#include <cmath>

float Graph::generateFunction(float x) const
{
    return float(a_) * x * x + float(b_) * x + float(c_);
}

std::string Graph::equation() const
{
    std::ostringstream ss;
    ss << "f(x) = ";

    if (a_ == 0 && b_ == 0) {
        ss << c_;
        return ss.str();
    }

    if (a_ != 0) {
        if (a_ == 1) ss << "x²";
        else if (a_ == -1) ss << "-x²";
        else               ss << a_ << "x²";
    }

    if (b_ != 0) {
        if (b_ == 1) ss << (a_ != 0 ? " + " : "") << "x";
        else if (b_ == -1) ss << (a_ != 0 ? " - " : "-") << "x";
        else if (b_ > 0) ss << (a_ != 0 ? " + " : "") << b_ << "x";
        else               ss << (a_ != 0 ? " - " : "") << -b_ << "x";
    }

    if (c_ != 0) {
        if (c_ > 0) ss << " + " << c_;
        else        ss << " - " << -c_;
    }

    return ss.str();
}

Graph::Graph()
    : curve_(sf::PrimitiveType::LineStrip)
{
}

void Graph::buildCurve(sf::Font& font)
{
    font_ = &font;
    curve_.clear();
    labels_.clear();

    const float gx0 = PAD_LEFT + MARGIN;
    const float gy0 = PAD_TOP + MARGIN + 30.f;
    const float gw = TABLET_W - 2.f * MARGIN;
    const float gh = TABLET_H - 2.f * MARGIN - 30.f;

    // Cas f(x) = 0
    if (a_ == 0 && b_ == 0 && c_ == 0) {
        originX_ = gx0 + gw / 2.f;
        originY_ = gy0 + gh / 2.f;
        xMin_ = -10.f; xMax_ = 10.f;
        yMin_ = -10.f; yMax_ = 10.f;
        scale_ = gw / 20.f;
    }
    else {
        const float xMin = -10.f, xMax = 10.f;

        float yMin = std::numeric_limits<float>::max();
        float yMax = std::numeric_limits<float>::lowest();
        for (float x = xMin; x <= xMax; x += 0.1f) {
            float y = generateFunction(x);
            yMin = std::min(yMin, y);
            yMax = std::max(yMax, y);
        }

        float marginY = (yMax - yMin) * 0.1f;
        if (marginY < 1.f) marginY = 1.f;
        float marginX = (xMax - xMin) * 0.1f;

        float domainX = (xMax - xMin) + 2.f * marginX;
        float domainY = (yMax - yMin) + 2.f * marginY;
        if (domainY < 2.f) domainY = 2.f;

        float scaleX = gw / domainX;
        float scaleY = gh / domainY;
        scale_ = std::min(scaleX, scaleY);

        xMin_ = xMin - marginX;
        xMax_ = xMax + marginX;
        yMin_ = yMin - marginY;
        yMax_ = yMax + marginY;

        originX_ = gx0 + (0.f - xMin_) * scale_;
        originY_ = gy0 + gh - (0.f - yMin_) * scale_;

        auto screenX = [&](float x) { return originX_ + x * scale_; };
        auto screenY = [&](float y) { return originY_ - y * scale_; };

        for (float x = xMin_; x <= xMax_; x += 0.05f) {
            float y = generateFunction(x);
            sf::Vertex v;
            v.position = { screenX(x), screenY(y) };
            v.color = sf::Color(70, 130, 220);
            curve_.append(v);
        }
    }

    // Précalcul des labels (fait une seule fois ici)
    float axisY = std::clamp(originY_, gy0, gy0 + gh);
    float axisX = std::clamp(originX_, gx0, gx0 + gw);

    // Labels X
    for (int i = (int)std::ceil(xMin_); i <= (int)std::floor(xMax_); ++i) {
        if (i == 0) continue;
        float sx = originX_ + i * scale_;
        if (sx < gx0 || sx > gx0 + gw) continue;
        sf::Text t(*font_, std::to_string(i), 9);
        t.setFillColor(sf::Color(80, 80, 80));
        float lw = t.getLocalBounds().size.x;
        t.setPosition({ sx - lw / 2.f, axisY + 6.f });
        labels_.push_back(std::move(t));
    }

    // Labels Y
    for (int j = (int)std::ceil(yMin_); j <= (int)std::floor(yMax_); ++j) {
        if (j == 0) continue;
        float sy = originY_ - j * scale_;
        if (sy < gy0 || sy > gy0 + gh) continue;
        sf::Text t(*font_, std::to_string(j), 9);
        t.setFillColor(sf::Color(80, 80, 80));
        float lw = t.getLocalBounds().size.x;
        float lh = t.getLocalBounds().size.y;
        t.setPosition({ axisX - lw - 8.f, sy - lh / 2.f });
        labels_.push_back(std::move(t));
    }

    // O
    sf::Text zero(*font_, "O", 9);
    zero.setFillColor(sf::Color(80, 80, 80));
    zero.setPosition({ axisX + 3.f, axisY + 3.f });
    labels_.push_back(std::move(zero));

    // Équation dans le bandeau
    sf::Text eq(*font_, equation(), 14);
    eq.setFillColor(sf::Color(220, 220, 255));
    eq.setPosition({ PAD_LEFT + 8.f, PAD_TOP + 6.f });
    labels_.push_back(std::move(eq));
}

void Graph::drawBackground(sf::RenderWindow& window)
{
    // Ombre
    sf::RectangleShape shadow({ TABLET_W, TABLET_H });
    shadow.setPosition({ PAD_LEFT + 6.f, PAD_TOP + 6.f });
    shadow.setFillColor(sf::Color(0, 0, 0, 60));
    window.draw(shadow);

    // Fond plan de travail
    sf::RectangleShape bg({ TABLET_W, TABLET_H });
    bg.setPosition({ PAD_LEFT, PAD_TOP });
    bg.setFillColor(sf::Color(245, 245, 240));
    bg.setOutlineColor(sf::Color(180, 170, 150));
    bg.setOutlineThickness(2.f);
    window.draw(bg);

    // Bandeau équation
    sf::RectangleShape banner({ TABLET_W, 30.f });
    banner.setPosition({ PAD_LEFT, PAD_TOP });
    banner.setFillColor(sf::Color(60, 60, 80));
    window.draw(banner);
}

void Graph::drawGrid(sf::RenderWindow& window)
{
    const float gx0 = PAD_LEFT + MARGIN;
    const float gy0 = PAD_TOP + MARGIN + 30.f;
    const float gw = TABLET_W - 2.f * MARGIN;
    const float gh = TABLET_H - 2.f * MARGIN - 30.f;

    sf::VertexArray grid(sf::PrimitiveType::Lines);

    for (int i = (int)std::ceil(xMin_); i <= (int)std::floor(xMax_); ++i) {
        float sx = originX_ + i * scale_;
        if (sx < gx0 || sx > gx0 + gw) continue;
        sf::Vertex v1, v2;
        v1.position = { sx, gy0 }; v1.color = sf::Color(210, 210, 200);
        v2.position = { sx, gy0 + gh }; v2.color = sf::Color(210, 210, 200);
        grid.append(v1); grid.append(v2);
    }

    for (int j = (int)std::ceil(yMin_); j <= (int)std::floor(yMax_); ++j) {
        float sy = originY_ - j * scale_;
        if (sy < gy0 || sy > gy0 + gh) continue;
        sf::Vertex v1, v2;
        v1.position = { gx0,      sy }; v1.color = sf::Color(210, 210, 200);
        v2.position = { gx0 + gw, sy }; v2.color = sf::Color(210, 210, 200);
        grid.append(v1); grid.append(v2);
    }

    window.draw(grid);
}

void Graph::drawAxes(sf::RenderWindow& window)
{
    const float gx0 = PAD_LEFT + MARGIN;
    const float gy0 = PAD_TOP + MARGIN + 30.f;
    const float gw = TABLET_W - 2.f * MARGIN;
    const float gh = TABLET_H - 2.f * MARGIN - 30.f;

    float axisY = std::clamp(originY_, gy0, gy0 + gh);
    float axisX = std::clamp(originX_, gx0, gx0 + gw);

    // Axes
    sf::VertexArray axes(sf::PrimitiveType::Lines, 4);
    axes[0].position = { gx0,      axisY }; axes[0].color = sf::Color(60, 60, 60);
    axes[1].position = { gx0 + gw, axisY }; axes[1].color = sf::Color(60, 60, 60);
    axes[2].position = { axisX,    gy0 }; axes[2].color = sf::Color(60, 60, 60);
    axes[3].position = { axisX, gy0 + gh }; axes[3].color = sf::Color(60, 60, 60);
    window.draw(axes);

    // Tous les labels précalculés d'un coup
    for (const auto& label : labels_)
        window.draw(label);
}

void Graph::draw(sf::RenderWindow& window, sf::Font& font)
{
    drawBackground(window);
    drawGrid(window);
    drawAxes(window);
    window.draw(curve_);
}