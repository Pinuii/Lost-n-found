#pragma once
#include "graph.h"
#include "TabletCurve.h"

class GameManager
{
public:
    GameManager(sf::Font& font);

    void onButtonPressed();   
    bool isGameWon() const { return score_ >= 5; }
    int  getScore()  const { return score_; }

    Graph& getGraph() { return graph_; }
    TabletCurve& getTablet() { return tablet_; }

private:
    Graph       graph_;   
    TabletCurve tablet_;  
    int         score_ = 0;
    sf::Font*   font_ = nullptr; 

    void nextRound();
    bool checkMatch() const;
};