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
#include "PauseMenu.h"
#include "FileManager.h"
#include "NameInput.h"


enum class GameState {
    Playing,
    GameOver,
	Paused,
    ExitToMenu
};

class Game {
private:
    sf::RenderWindow& _window; // La ventana principal para renderizar
    Player _player;
    std::vector<Enemy> _enemies; // Vector para almacenar enemigos
    std::vector<ExpOrb> _expOrbs;
    Spawner _spawner; 

    int _ultimoNivel = 1;
    
    // Boss
    bool _bossSpawned = false;
    bool _bossAparecio = false;
    
    sf::View _camera;
    sf::Texture _backgroundTexture;
    sf::Sprite _backgroundSprite;
    sf::Texture _bossBackgroundTexture;  
    bool _bossBackgroundActive;

    float dt;
    GameState _state = GameState::Playing;
    PauseMenu _pauseMenu;
	FileManager _fileManager; 


    // Mariano elementos del HUD
	sf::Font _font; 
    sf::Text _levelText;
    sf::RectangleShape _expBarBackground;
    sf::RectangleShape _expBarFill;
    float _timer;
    sf::Text _timerTexto;
    int _puntuacion;
    sf::Text _textoPuntuacion;
    sf::Sprite _playerIcon;
    sf::Texture _playerIconTexture;
    sf::Text _statsText;
    sf::RectangleShape _statsBackground;


    //Ema - Musica y sonidos
    sf::Music musicaFondo;
	sf::Music musicaBoss;
    sf::SoundBuffer bufferAtaque;
    sf::Sound sonidoAtaque;

    //pantalla game over
    sf::Text _gameOverText;
	sf::Clock _gameOverClock;
    sf::RectangleShape _gameOverBackground;
    sf::Text _gameOverPrompt;

    //Escalado de stats
    int _mejorasAplicadas = 0;
    float _aumentoDanio = 0.f;
    float _aumentoVelocidad = 0.f;
    float _aumentoVida = 0.f;

    void processEvents();
    void update(float deltaTime);
    void updatePlayerStatsDisplay();
    void render();
    void checkCollisions();
    void checkHitpoints();
    bool _shouldExitToMenu;
    sf::Vector2f getClosestEnemy();

public:

    Game(sf::RenderWindow& window);
    bool loadSave();
    void run();
    bool shouldExitToMenu() const { return _shouldExitToMenu; }
    void setPlayerName(const std::string& name) { _player.setName(name); }
};

#endif