#ifndef SCOREMENU_H
#define SCOREMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <algorithm> // Para std::sort
#include "FileManager.h" // Necesitamos ScoreEntry y FileManager para leer
#include "Globals.h"     // Para WINDOW_WIDTH, WINDOW_HEIGHT (si no los usas directamente, los puedes quitar)

class ScoreMenu {
private:
    sf::RenderWindow& _window; // Referencia a la ventana de SFML
    sf::Font _font;            // Fuente para el texto
    std::vector<sf::Text> _scoreTexts; // Textos individuales para cada puntuaci�n
    sf::Text _titleText;       // T�tulo de la pantalla de puntuaciones
    sf::Text _returnPrompt;    // Mensaje para volver al men�
    sf::RectangleShape _background; // Fondo semitransparente para la pantalla

    // M�todo auxiliar para ordenar las puntuaciones y preparar los textos
    void sortAndDisplayScores(std::vector<ScoreEntry>& scores);

public:
    // Constructor: Recibe la ventana para poder dibujar en ella
    ScoreMenu(sf::RenderWindow& window);
    // Muestra la pantalla de puntuaciones y maneja su bucle de eventos
    void showScores(const std::vector<ScoreEntry>& allScores);
};

#endif