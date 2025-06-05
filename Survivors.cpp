#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"
#include "Globals.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mini Survivors - Menú");
    Menu menu(WINDOW_WIDTH, WINDOW_HEIGHT);
    Game game(window);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W)
                    menu.moveUp();
                else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
                    menu.moveDown();
                else if (event.key.code == sf::Keyboard::Enter) {
                    int selected = menu.getSelectedIndex();
                    switch (selected) {
                    case 0: /* Continuar */ break;
                    case 1: 
                        game.run();
                        break;
                    case 2: /* Opciones */ break;
                    case 3: /* Puntuaciones */ break;
                    case 4: window.close(); break;
                    }
                }
            }
        }

        window.clear();
        menu.draw(window);
        window.display();
    }
    

    return 0;
}
