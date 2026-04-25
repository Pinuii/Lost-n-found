#include "GameManager.h"

GameManager::GameManager(sf::Font& font)
	: font_(&font)
{
    nextRound();
}

void GameManager::nextRound()
{
    tablet_.randomize();          
    tablet_.buildCurve();
    graph_.resetPlayer();         // remet le joueur à f(x) = 0
    graph_.buildCurve(*font_);
}

bool GameManager::checkMatch() const
{

    return graph_.getA() == tablet_.getA()
        && graph_.getB() == tablet_.getB()
        && graph_.getC() == tablet_.getC();
}

void GameManager::onButtonPressed()
{
    graph_.buildCurve(*font_);
    if (checkMatch()) {
        score_++;
        if (!isGameWon())
            nextRound();
    }
}