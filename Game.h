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
    sf::RenderWindow _window;
    Player _player;
    std::vector<Enemy> _enemies;
    Spawner _spawner;

    void processEvents();
    void update(float deltaTime);
    void render();

public:
    Game();
    void run();
};

#endif
