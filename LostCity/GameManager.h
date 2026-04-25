#pragma once
#include "graph.h"
#include "TabletCurve.h"

class GameManager
{
public:
    GameManager(sf::Font& font);

    void onButtonPressed();   // appelé par chaque bouton après modification
    bool isGameWon() const { return score_ >= 5; }
    int  getScore()  const { return score_; }

    Graph& getGraph() { return graph_; }
    TabletCurve& getTablet() { return tablet_; }

private:
    Graph       graph_;   // plan de travail du joueur
    TabletCurve tablet_;  // courbe secrète
    int         score_ = 0;
    sf::Font*   font_ = nullptr; // Ajout du membre font_

    void nextRound();
    bool checkMatch() const;
};