#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class PauseMenu {
private:
    sf::Font _font;
    std::vector<sf::Text> _options;
    int _selectedIndex;
    sf::RectangleShape _background;

public:
    PauseMenu(float width, float height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;
};

#endif
