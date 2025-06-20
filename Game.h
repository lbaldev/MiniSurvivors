#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "Spawner.h"
#include "Globals.h"
#include "Entity.h"
#include "ExpOrb.h"




class Game {
private:
	sf::RenderWindow& _window; // La ventana principal para renderizar
    Player _player;
	std::vector<Enemy> _enemies; // Vector para almacenar enemigos
    std::vector<ExpOrb> _expOrbs;
    Spawner _spawner;
    sf::View _camera;
    sf::Texture _backgroundTexture;
    sf::Sprite _backgroundSprite;
    float dt;
    // Mariano elementos del HUD
	sf::Font _font; // Fuente para el HUD
    sf::Text _levelText;
    sf::RectangleShape _expBarBackground;
    sf::RectangleShape _expBarFill;
    sf::Clock _timer;
    sf::Text _timerTexto;
    int _puntuacion;
    sf::Text _textoPuntuacion;

    void processEvents();
    void update(float deltaTime);
    void render();
	void checkCollisions();
    void checkHitpoints();

public:
    Game(sf::RenderWindow& window);
    void run();
};

#endif
