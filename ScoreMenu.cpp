#include "ScoreMenu.h"
#include "Globals.h" // Para WINDOW_WIDTH, WINDOW_HEIGHT
#include <iostream>  // Para depuración
#include <algorithm> // Para std::min

ScoreMenu::ScoreMenu(sf::RenderWindow& window, sf::Font& font)
    : _window(window), _font(font) { // La fuente ahora se pasa, no se carga aquí.

    _titleText.setFont(_font);
    _titleText.setString("TOP 10 PUNTUACIONES");
    _titleText.setCharacterSize(48);
    _titleText.setFillColor(sf::Color::Yellow);
    _titleText.setOrigin(_titleText.getLocalBounds().width / 2, _titleText.getLocalBounds().height / 2);
    _titleText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 200);

    _returnPrompt.setFont(_font);
    _returnPrompt.setString("Presione ESC para volver al menu.");
    _returnPrompt.setCharacterSize(24);
    _returnPrompt.setFillColor(sf::Color::Cyan);
    _returnPrompt.setOrigin(_returnPrompt.getLocalBounds().width / 2, _returnPrompt.getLocalBounds().height / 2);
    _returnPrompt.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50);

    _background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    _background.setFillColor(sf::Color(0, 0, 0, 180));
}

// Implementación del ordenamiento, similar a cómo buscarías el máximo en un array
// Usaremos un algoritmo de selección simple para ordenar de mayor a menor.
void ScoreMenu::_sortScores(std::vector<ScoreEntry>& scores) {
    int n = scores.size();
    for (int i = 0; i < n - 1; ++i) {
        int maxIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (scores[j].puntuacion > scores[maxIndex].puntuacion) {
                maxIndex = j;
            }
        }
        // Intercambiar el elemento encontrado con el primer elemento no ordenado
        if (maxIndex != i) {
            ScoreEntry temp = scores[i];
            scores[i] = scores[maxIndex];
            scores[maxIndex] = temp;
        }
    }
}

// Esta función obtiene los 10 mejores puntajes después de ordenarlos.
std::vector<ScoreEntry> ScoreMenu::_getTop10(const std::vector<ScoreEntry>& allScores) {
    std::vector<ScoreEntry> top10;
    // allScores ya viene ordenada de mayor a menor por _sortScores
    for (size_t i = 0; i < std::min((size_t)10, allScores.size()); ++i) {
        top10.push_back(allScores[i]);
    }
    return top10;
}


void ScoreMenu::run(FileManager& fileManager) {
    // 1. Leer todos los puntajes del archivo
    std::vector<ScoreEntry> allScores = fileManager.leerPuntajes();
    // Nota: Si ya ordenas en FileManager::leerPuntajes(), esta línea sobra.
    // Si no, debes llamarla aquí:
    _sortScores(allScores);

    // 2. Obtener el top 10 (o menos si hay menos de 10)
    std::vector<ScoreEntry> topScores = _getTop10(allScores);

    bool displayingScores = true;
    while (_window.isOpen() && displayingScores) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    displayingScores = false;
                }
            }
        }

        _window.clear();
        _window.draw(_background);
        _window.draw(_titleText);

        // Dibuja las entradas de puntuación
        for (size_t i = 0; i < topScores.size(); ++i) {
            sf::Text scoreText;
            scoreText.setFont(_font);
            scoreText.setCharacterSize(30);
            scoreText.setFillColor(sf::Color::White);

            std::string entryString = std::to_string(i + 1) + ". " + topScores[i].nombre + " - " + std::to_string(topScores[i].puntuacion);
            scoreText.setString(entryString);

            // Centrar el texto
            sf::FloatRect textRect = scoreText.getLocalBounds();
            scoreText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
            scoreText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100 + i * 40);

            _window.draw(scoreText);
        }
        _window.draw(_returnPrompt);
        _window.display();
    }
}