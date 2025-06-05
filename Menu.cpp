#include "Menu.h"

Menu::Menu(float width, float height) : _selectedIndex(0) {
    _options = { "Continuar", "Nueva Partida", "Opciones", "Puntuaciones", "Salir" };

    if (!_font.loadFromFile("assets/font.otf")) {
        // Error de fuente
    }

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

void Menu::draw(sf::RenderWindow& window) {
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
