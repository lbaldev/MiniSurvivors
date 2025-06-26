#ifndef SCOREMENU_H
#define SCOREMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "FileManager.h"

class ScoreMenu {
private:
    sf::RenderWindow& _window;
    sf::Font _font;
    sf::Text _titleText;
    sf::Text _returnPrompt;
    sf::RectangleShape _background;

    void _sortScores(std::vector<ScoreEntry>& scores); 
    std::vector<ScoreEntry> _getTop10(const std::vector<ScoreEntry>& allScores); 

public:
    ScoreMenu(sf::RenderWindow& window, sf::Font& font);
    void run(FileManager& fileManager);
};

#endif