#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
private:
    std::vector<std::string> _options;
    std::vector<sf::Text> _texts;
    sf::Font _font;
    int _selectedIndex;

public:
    Menu(float width, float height);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedIndex() const;
};

#endif
