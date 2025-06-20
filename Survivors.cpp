#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"
#include "Globals.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mini Survivors - Menú");

    while (window.isOpen()) {
        Menu menu(WINDOW_WIDTH, WINDOW_HEIGHT);
        bool showMenu = true;

        while (window.isOpen() && showMenu) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                        menu.moveUp();
                    }
                    else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                        menu.moveDown();
                    }
                    else if (event.key.code == sf::Keyboard::Enter) {
                        int selected = menu.getSelectedIndex();
                        switch (selected) {
                        case 1: {  
                            Game game(window);
                            game.run();

                            if (game.shouldExitToMenu()) {
                                showMenu = true;  
                            }
                            else {
                                window.close();  
                            }
                            break;
                        }
                        case 4:  
                            window.close();
                            break;
                            
                        }

                    }
                }
            }
            window.clear();
            menu.draw(window);
            window.display();
        }
    }
    return 0;
}