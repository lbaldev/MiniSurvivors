#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Menu.h"
#include "Globals.h"
#include "NameInput.h"
#include "FileManager.h"
#include "ScoreMenu.h"  

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mini Survivors - Menú");
    FileManager fileManager("save.txt", "puntajes.txt");

    sf::Font mainFont;
    if (!mainFont.loadFromFile("assets/font.otf")) {
        std::cerr << "Error cargando fuente principal. Asegurate de que 'assets/font.otf' exista." << std::endl;
        return -1;
    }

    ScoreMenu scoreScreen(window, mainFont);

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
                        menu.playSelectSound();
                        int selected = menu.getSelectedIndex();
                        Game game(window);
                        switch (selected) {
                        case 0: {
                            if (game.loadSave()) game.run();
                            break;
                        }
                        
                        case 1: {
                            NameInput nameScreen(window);
                            if (nameScreen.run()) {
                                game.setPlayerName(nameScreen.getPlayerName());
                                game.run(); // Ahora game puede acceder al nombre con nameScreen.getPlayerName()
                            }
                            break;
                        }   
                        case 3: { // Puntuaciones
                            scoreScreen.run(fileManager);
                            showMenu = true; // Vuelve al menú después de ver los scores
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