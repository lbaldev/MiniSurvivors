#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <SFML/Audio.hpp>

class Menu {
private:
    std::vector<std::string> _options;
    std::vector<sf::Text> _texts;
    sf::Font _font;
    int _selectedIndex;
    sf::Texture _backgroundTexture;  // Textura de fondo
    sf::Sprite _backgroundSprite;    // Sprite de fondo
    sf::SoundBuffer _moveSoundBuffer;
    sf::SoundBuffer _selectSoundBuffer;
    sf::Sound _moveSound;
    sf::Sound _selectSound;

public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;
    bool loadBackground(const std::string& filename); // M�todo para cargar el fondo
    void playSelectSound();
};

#endif