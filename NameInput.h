#ifndef NAMEINPUT_H
#define NAMEINPUT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

class NameInput {
private:
    sf::RenderWindow& _window;
    sf::Font _font;
    sf::Text _titleText;
    sf::Text _inputText;
    sf::RectangleShape _inputBox;
    std::string _playerName;
    bool _nameConfirmed;
    sf::Sound _typingSound;
    sf::Sound _selectSound;
    sf::SoundBuffer _typingSoundBuffer;
    sf::SoundBuffer _selectSoundBuffer;
    sf::Clock _cursorClock;
    bool _showCursor;

public:
    NameInput(sf::RenderWindow& window);
    bool run();
    const std::string& getPlayerName() const { return _playerName; }
};

#endif