#include "Menu.h"
#include "Globals.h"

Menu::Menu(float width, float height) : _selectedIndex(0) {
    _options = { "Continuar", "Nueva Partida", "Opciones", "Puntuaciones", "Salir" };

    if (!_font.loadFromFile("assets/font.otf")) {
        // Manejar error de carga de fuente
    }

    // Cargar imagen de fondo
    if (!_backgroundTexture.loadFromFile("assets/menu_background.png")) {
        // Si falla, puedes usar un color sólido como respaldo
        _backgroundTexture.create(width, height);
    }
    _backgroundSprite.setTexture(_backgroundTexture);

    // Ajustar tamaño si es necesario
    _backgroundSprite.setScale(
        width / _backgroundSprite.getLocalBounds().width,
        height / _backgroundSprite.getLocalBounds().height
    );

    // Hace el texto con todas las opciones
    for (size_t i = 0; i < _options.size(); ++i) {
        sf::Text text;
        text.setFont(_font);
        text.setString(_options[i]);
        text.setCharacterSize(36);
        text.setFillColor(i == _selectedIndex ? sf::Color::Yellow : sf::Color::White);
        text.setPosition(width / 2 - 100, height / 2 + i * 50);
        _texts.push_back(text);
    }
}

bool Menu::loadBackground(const std::string& filename) {
    return _backgroundTexture.loadFromFile(filename);
}

void Menu::draw(sf::RenderWindow& window) {
    // Dibujar fondo primero
    window.draw(_backgroundSprite);

    // Dibujar un rectángulo semitransparente detrás del texto
    sf::RectangleShape background(sf::Vector2f(400, 300));
    background.setFillColor(sf::Color(0, 0, 0, 150)); // Negro semitransparente
    background.setPosition(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 10);
    window.draw(background);

    // Luego dibujar los textos del menú
    for (const auto& text : _texts) {
        window.draw(text);
    }
}

void Menu::moveUp() {
    if (_selectedIndex > 0) {
        _texts[_selectedIndex].setFillColor(sf::Color::White);
        _selectedIndex--;
        _texts[_selectedIndex].setFillColor(sf::Color::Yellow);
    }
}

void Menu::moveDown() {
    if (_selectedIndex < static_cast<int>(_texts.size()) - 1) {
        _texts[_selectedIndex].setFillColor(sf::Color::White);
        _selectedIndex++;
        _texts[_selectedIndex].setFillColor(sf::Color::Yellow);
    }
}

int Menu::getSelectedIndex() const {
    return _selectedIndex;
}
