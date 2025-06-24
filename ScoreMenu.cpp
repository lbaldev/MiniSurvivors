#include "ScoreMenu.h"
#include <iostream> // Para manejo de errores con cerr



ScoreMenu::ScoreMenu(sf::RenderWindow& window) : _window(window) {
    // Carga de la fuente
    if (!_font.loadFromFile("assets/font.otf")) {
        std::cerr << "Error cargando fuente para ScoreDisplay. Asegurate de que 'assets/font.otf' exista." << std::endl;
        // Podrías lanzar una excepción o usar una fuente por defecto aquí
    }

    // Configuración del texto del título
    _titleText.setFont(_font);
    _titleText.setString("TOP 10 PUNTUACIONES");
    _titleText.setCharacterSize(48);
    _titleText.setFillColor(sf::Color::Yellow);
    // Centrar el título
    _titleText.setOrigin(_titleText.getLocalBounds().width / 2, _titleText.getLocalBounds().height / 2);
    _titleText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 200);

    // Configuración del mensaje para volver
    _returnPrompt.setFont(_font);
    _returnPrompt.setString("Presione ESC para volver al menu.");
    _returnPrompt.setCharacterSize(24);
    _returnPrompt.setFillColor(sf::Color::Cyan);
    // Centrar el mensaje
    _returnPrompt.setOrigin(_returnPrompt.getLocalBounds().width / 2, _returnPrompt.getLocalBounds().height / 2);
    _returnPrompt.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50);

    // Configuración del fondo semitransparente
    _background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    _background.setFillColor(sf::Color(0, 0, 0, 180)); // Negro con 180 de opacidad (de 255)
}

void ScoreMenu::sortAndDisplayScores(std::vector<ScoreEntry>& scores) {
    // 1. Ordenar las puntuaciones de mayor a menor
    std::sort(scores.begin(), scores.end(), [](const ScoreEntry& a, const ScoreEntry& b) {
        return a.puntuacion > b.puntuacion;
        });

    // 2. Limpiar los textos de puntuaciones anteriores
    _scoreTexts.clear();

    // 3. Crear nuevos textos para el top 10 (o menos si hay menos de 10)
    for (size_t i = 0; i < std::min((size_t)10, scores.size()); ++i) {
        sf::Text scoreText;
        scoreText.setFont(_font);
        scoreText.setCharacterSize(30);
        scoreText.setFillColor(sf::Color::White);

        // Formatear la cadena de la puntuación (ej: "1. Nombre - Puntuacion")
        std::string entryString = std::to_string(i + 1) + ". " + scores[i].nombre + " - " + std::to_string(scores[i].puntuacion);
        scoreText.setString(entryString);

        // Centrar cada entrada horizontalmente
        scoreText.setOrigin(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2);
        // Posicionar verticalmente, espaciando cada entrada
        scoreText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 100 + i * 40); // Ajusta 100 y 40 para el espaciado
        _scoreTexts.push_back(scoreText);
    }
}

void ScoreMenu::showScores(const std::vector<ScoreEntry>& allScores) {
    // Se hace una copia para poder ordenar el vector sin modificar el original si viniera como const
    std::vector<ScoreEntry> scoresCopy = allScores;
    sortAndDisplayScores(scoresCopy); // Prepara los textos y los ordena

    bool displayingScores = true;
    while (_window.isOpen() && displayingScores) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close(); // Cerrar la ventana del juego si se cierra la pantalla de puntuaciones
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    displayingScores = false; // Salir de la pantalla de puntuaciones al presionar ESC
                }
            }
        }

        // Dibujo
        _window.clear(); // Limpia la ventana
        _window.draw(_background); // Dibuja el fondo semitransparente
        _window.draw(_titleText);  // Dibuja el título

        // Dibuja cada entrada de puntuación
        for (const auto& text : _scoreTexts) {
            _window.draw(text);
        }
        _window.draw(_returnPrompt); // Dibuja el mensaje para volver
        _window.display(); // Muestra todo en pantalla
    }
}