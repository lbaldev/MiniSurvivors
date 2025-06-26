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

    // Métodos privados para la lógica de puntuaciones,
    // implementados de forma que te sean más familiares.
    void _sortScores(std::vector<ScoreEntry>& scores); // Para ordenar el vector
    std::vector<ScoreEntry> _getTop10(const std::vector<ScoreEntry>& allScores); // Para obtener el top 10

public:
    ScoreMenu(sf::RenderWindow& window, sf::Font& font);
    void run(FileManager& fileManager);
};

#endif