#include "game.hpp"
#include "sprite.hpp"

#include <stdexcept>

Game::Game() 
{}

Game::~Game()
{
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Game::initSystems()
{
    if(SDL_Init(SDL_INIT_VIDEO))
	throw std::runtime_error("SDL_Init failed");

    window_ = SDL_CreateWindow("Arider", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			       width_, height_, SDL_WINDOW_OPENGL);
    if(window_ == nullptr)
	throw std::runtime_error("SDL_CreateWindow failed");

    SDL_GLContext glContext = SDL_GL_CreateContext(window_);
    if(glContext == nullptr)
	throw std::runtime_error("SDL_GL_CreateContext failed");

    GLenum error = glewInit();
    if(error != GLEW_OK)
	throw std::runtime_error("glewInit failed");

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    glClearColor(0.f, 0.f, 1.f, 1.f);
}

void Game::processInput()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
	switch(event.type)
	{
	case SDL_QUIT:
	    game_state_ = GameState::EXIT;
	}
    }
}

void Game::gameLoop()
{
    Sprite sprite;
    sprite.init(-1.f, -1.f, 1.f, 1.f);
    while(game_state_ != GameState::EXIT)
    {
	processInput();
	sprite.draw();
	drawGame();
    }
}

void Game::drawGame()
{
    glClearDepth(1.0);
    // clears buffer with clear color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // swap buffer and draw everything to the screen
    SDL_GL_SwapWindow(window_);
}

void Game::run()
{
    initSystems();
    gameLoop();
}
