#ifndef GAME_HPP
#define GAME_HPP

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <glm/glm.hpp>

#include <YAGE/glslprogram.hpp>
#include <YAGE/camera2d.hpp>
#include <YAGE/gltexture.hpp>
#include <YAGE/sprite.hpp>
#include <YAGE/window.hpp>

#include <memory>
#include <vector>

enum class GameState
{
    PLAY,
    EXIT
};

class Game
{
public: // member variables
private:
    // screen width and height initialized in constructor
    int screen_width_;
    int screen_height_;
    // initializer game state
    GameState game_state_=GameState::PLAY;
    // set timer to 0
    float time_=0;
    // window
    yage::Window window_;
    // camera
    yage::Camera2D camera_;
    // temporary program
    yage::GlslProgram program_;
    std::vector<std::shared_ptr<yage::Sprite>> sprites_;

public: // member functions
    Game(int screen_width=1280, int screen_height=720);
    ~Game();

    void run();
private:
    void initSystems();
    void initShaders();
    void processInput();
    void gameLoop();
    void drawGame();
    float calculateFps();
};

#endif
