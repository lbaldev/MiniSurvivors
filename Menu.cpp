#include "Menu.h"
#include "Globals.h"

Menu::Menu(float width, float height) : _selectedIndex(0) {
    _options = { "Continuar", "Nueva Partida", "Puntuaciones", "Salir" };

    if (!_font.loadFromFile("assets/font.otf")) {
        // vamos viendo
    }

    // Cargar imagen de fondo
    if (!_backgroundTexture.loadFromFile("assets/menu_background.png")) {
        _backgroundTexture.create(width, height);
    }
    _backgroundSprite.setTexture(_backgroundTexture);
    _backgroundSprite.setScale(
        width / _backgroundSprite.getLocalBounds().width,
        height / _backgroundSprite.getLocalBounds().height
    );

    //sonidos
    _moveSoundBuffer.loadFromFile("assets/menu_move.ogg");
    _selectSoundBuffer.loadFromFile("assets/menu_select.ogg");
    _moveSound.setBuffer(_moveSoundBuffer);
    _selectSound.setBuffer(_selectSoundBuffer);

    //texto opciones
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
    window.draw(_backgroundSprite);
    sf::RectangleShape background(sf::Vector2f(400, 300));
    background.setFillColor(sf::Color(0, 0, 0, 150)); 
    background.setPosition(WINDOW_WIDTH / 2 - 200, WINDOW_HEIGHT / 2 - 10);
    window.draw(background);

    for (const auto& text : _texts) {
        window.draw(text);
    }
}

void Menu::moveUp() {
    if (_selectedIndex > 0) {
        _texts[_selectedIndex].setFillColor(sf::Color::White);
        _selectedIndex--;
        _texts[_selectedIndex].setFillColor(sf::Color::Yellow);
        _moveSound.play(); 
    }
}

void Menu::moveDown() {
    if (_selectedIndex < static_cast<int>(_texts.size()) - 1) {
        _texts[_selectedIndex].setFillColor(sf::Color::White);
        _selectedIndex++;
        _texts[_selectedIndex].setFillColor(sf::Color::Yellow);
        _moveSound.play();
    }
}

void Menu::playSelectSound() {
    if (_selectSound.getStatus() != sf::Sound::Playing) {
        _selectSound.play();
    }
}

int Menu::getSelectedIndex() const {
    return _selectedIndex;
}
