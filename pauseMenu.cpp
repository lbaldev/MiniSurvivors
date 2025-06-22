#include "PauseMenu.h"

PauseMenu::PauseMenu(float width, float height) : _selectedIndex(0) {
    

    std::vector<std::string> labels = { "Continuar", "Guardar partida", "Salir" };
    _font.loadFromFile("assets/font.otf");
    for (size_t i = 0; i < labels.size(); ++i) {
        sf::Text text;
        text.setFont(_font);
        text.setString(labels[i]);
        text.setCharacterSize(40);
        text.setFillColor(i == _selectedIndex ? sf::Color::Yellow : sf::Color::White);
        text.setPosition(width / 2.f - 100.f, height / 2.f + i * 60.f);
        _options.push_back(text);
    }

    _background.setSize(sf::Vector2f(width, height));
    _background.setFillColor(sf::Color(0, 0, 0, 150));  // semitransparente
}

void PauseMenu::draw(sf::RenderWindow& window) {
    window.draw(_background);
    for (auto& option : _options)
        window.draw(option);
}

void PauseMenu::moveUp() {
    if (_selectedIndex > 0) {
        _options[_selectedIndex].setFillColor(sf::Color::White);
        _selectedIndex--;
        _options[_selectedIndex].setFillColor(sf::Color::Yellow);
    }
}

void PauseMenu::moveDown() {
    if (_selectedIndex < _options.size() - 1) {
        _options[_selectedIndex].setFillColor(sf::Color::White);
        _selectedIndex++;
        _options[_selectedIndex].setFillColor(sf::Color::Yellow);
    }
}

int PauseMenu::getSelectedIndex() const {
    return _selectedIndex;
}
