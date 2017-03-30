#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <GL/glew.h>

enum class GameState
{
    PLAY,
    EXIT
};

class Game
{
private:
    SDL_Window *window_ = nullptr;
    int width_ = 1280;
    int height_ = 720;
    GameState game_state_ = GameState::PLAY;

    void initSystems();
    void processInput();
    void gameLoop();
    void drawGame();
public:
    Game();
    ~Game();

    void run();
};

#endif
