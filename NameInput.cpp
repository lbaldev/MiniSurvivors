#include "NameInput.h"
#include "Globals.h"

NameInput::NameInput(sf::RenderWindow& window)
    : _window(window), _playerName(""), _nameConfirmed(false), _showCursor(true) {

    // Configuración visuall
    _font.loadFromFile("assets/font.otf");

    _titleText.setFont(_font);
    _titleText.setString("INGRESE SU NOMBRE:");
    _titleText.setCharacterSize(30);
    _titleText.setFillColor(sf::Color::White);
    _titleText.setOrigin(_titleText.getLocalBounds().width / 2, _titleText.getLocalBounds().height / 2);
    _titleText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 50);

    _inputBox.setSize(sf::Vector2f(300, 40));
    _inputBox.setFillColor(sf::Color(30, 30, 30, 200));
    _inputBox.setOutlineThickness(1);
    _inputBox.setOutlineColor(sf::Color::White);
    _inputBox.setOrigin(_inputBox.getSize().x / 2, _inputBox.getSize().y / 2);
    _inputBox.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 20);

    _inputText.setFont(_font);
    _inputText.setCharacterSize(24);
    _inputText.setFillColor(sf::Color::White);
    _inputText.setPosition(_inputBox.getPosition().x - _inputBox.getSize().x / 2 + 10, _inputBox.getPosition().y - 15);

    // Sonido
    _typingSoundBuffer.loadFromFile("assets/menu_move.ogg"); 
    _selectSoundBuffer.loadFromFile("assets/menu_select.ogg");
    _typingSound.setBuffer(_typingSoundBuffer);
    _selectSound.setBuffer(_selectSoundBuffer);
    _typingSound.setVolume(70);
    _selectSound.setVolume(70);

}

bool NameInput::run() {
    _cursorClock.restart();
    while (_window.isOpen() && !_nameConfirmed) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
                return false;
            }

            //Volver al menú sin guardar
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                return false; 
            }

            // Input de texto
            if (event.type == sf::Event::TextEntered) {
                char c = static_cast<char>(event.text.unicode); 

                if (std::isalnum(c) || c == ' ' || c == '\b') {
                    if (c == '\b' && !_playerName.empty()) { 
                        _playerName.pop_back();
                        _typingSound.play();
                    }
                    else if (_playerName.size() < 15 && c != '\b') { 
                        _playerName += c;
                        _typingSound.play();
                    }
                    _inputText.setString(_playerName);
                }
            }

            // Confirmar con Enter
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && !_playerName.empty()) {
                _selectSound.play();
                _nameConfirmed = true;
            }
        }
        // Cursor intermitente
        if (_cursorClock.getElapsedTime().asSeconds() > 0.5f) {
            _showCursor = !_showCursor;
            _cursorClock.restart();
        }
        _inputText.setString(_playerName + (_showCursor ? "_" : ""));

        // Render
        _window.clear(sf::Color(20, 20, 40));
        _window.draw(_titleText);
        _window.draw(_inputBox);
        _window.draw(_inputText);
        _window.display();
    }
    return _nameConfirmed;
}