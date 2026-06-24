#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#include <AudioManager.h>
#include <GameConfig.h>
#include <GameSession.h>
#include <ItemCombinationDatabase.h>
#include <ItemDatabase.h>
#include <MilestoneDatabase.h>
#include <SceneLoader.h>
#include <UiBackdrop.h>
#include <memory>
#include <string>

namespace highline_ridge
{

class GameApplication
{
    public:
    int run(int argc, char* argv[]);

    private:
    bool locateGameResources();
    bool initializeWindow(const GameConfig& gameConfig);
    bool loadDatabases();
    void shutdown();

    GameConfig gameConfig;
    std::string gameConfigPath = "resources/game_config.json";
    AudioManager audioManager;
    SceneDatabase sceneDatabase;
    MilestoneDatabase milestoneDatabase;
    ItemDatabase itemDatabase;
    ItemCombinationDatabase itemCombinationDatabase;
    UiBackdrop uiBackdrop;
    std::unique_ptr<GameSession> session;
};

}

#endif /* GAME_APPLICATION_H */