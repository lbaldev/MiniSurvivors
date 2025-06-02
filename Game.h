#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "Spawner.h"
#include "Globals.h"


class Game {
private:
	sf::RenderWindow _window; // La ventana principal para renderizar
    Player _player;
	std::vector<Enemy> _enemies; // Vector para almacenar enemigos
    Spawner _spawner;
    sf::View _camera;

    void processEvents();
    void update(float deltaTime);
    void render();
	void checkCollisions();


public:
    Game();
    void run();
};

#endif
