#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "ExpOrb.h"

struct ScoreEntry {
    char nombre[30];
    int puntuacion;
};

class FileManager {
private:
    std::string _archivoPartida;
    std::string _archivoPuntajes;

public:
    FileManager(const std::string& archivoPartida, const std::string& archivoPuntajes);

    bool guardarPartida(const Player& jugador, const std::vector<Enemy>& enemigos, const std::vector<ExpOrb>& orbes, float& tiempo, int& puntuacion);
    bool cargarPartida(Player& jugador, std::vector<Enemy>& enemigos, std::vector<ExpOrb>& orbes, float& tiempo, int& puntuacion);

    bool guardarPuntaje(const ScoreEntry& entry);
    std::vector<ScoreEntry> leerPuntajes();
};

#endif