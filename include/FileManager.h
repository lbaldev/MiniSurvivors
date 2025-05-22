#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include "Player.h"

struct ScoreEntry {
    char name[30];
    int score;
};

class FileManager {
private:
    std::string _saveFile;
    std::string _scoreFile;

public:
    FileManager(const std::string& saveFile, const std::string& scoreFile);

    bool saveGame(const Player& player);
    bool loadGame(Player& player);

    bool saveScores(const std::vector<ScoreEntry>& scores);
    std::vector<ScoreEntry> loadScores();
};

#endif
