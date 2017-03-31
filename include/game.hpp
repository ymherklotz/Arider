#ifndef GAME_HPP
#define GAME_HPP

#include "glsl_program.hpp"
#include "gl_texture.hpp"
#include "sprite.hpp"

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
    float time_ = 0;

    // Temporary program
    GlslProgram program_;
    GlTexture player_texture_;
    Sprite sprite_;

    void initSystems();
    void initShaders();
    void processInput();
    void gameLoop();
    void drawGame();
public:
    Game();
    ~Game();

    void run();
};

#endif
