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
#include <SFML/Audio.hpp>


enum class GameState {
    Playing,
    GameOver,
    ExitToMenu
};

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
    GameState _state = GameState::Playing;

    // Mariano elementos del HUD
	sf::Font _font; // Fuente para el HUD
    sf::Text _levelText;
    sf::RectangleShape _expBarBackground;
    sf::RectangleShape _expBarFill;
    sf::Clock _timer;
    sf::Text _timerTexto;
    int _puntuacion;
    sf::Text _textoPuntuacion;

    //Ema - Musica y sonidos
    sf::Music musicaFondo;
    sf::SoundBuffer bufferAtaque;
    sf::Sound sonidoAtaque;
    //pantalla game over
    sf::Text _gameOverText;
	sf::Clock _gameOverClock;
    sf::RectangleShape _gameOverBackground;
    sf::Text _gameOverPrompt;



    void processEvents();
    void update(float deltaTime);
    void render();
    void checkCollisions();
    void checkHitpoints();
    bool _shouldExitToMenu;
    sf::Vector2f getClosestEnemy();

public:
    Game(sf::RenderWindow& window);
    void run();
    bool shouldExitToMenu() const { return _shouldExitToMenu; }
};

#endif