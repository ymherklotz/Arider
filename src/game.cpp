#include "animation.hpp"
#include "game.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include <YAGE/texture.hpp>
#include <YAGE/resourcemanager.hpp>
#include <YAGE/vertex.hpp>

#include <stdexcept>
#include <iostream>

Game::Game(int screen_width/*=1280*/, int screen_height/*=720*/) :
    screen_width_(screen_width),
    screen_height_(screen_height),
    camera_(screen_width_, screen_height_)
{}

Game::~Game()
{
    SDL_Quit();
}

void Game::run()
{
    initSystems();    
    sprite_batch_.init();
    gameLoop();
}

void Game::initSystems()
{
    if(SDL_Init(SDL_INIT_VIDEO))
	throw std::runtime_error("SDL_Init failed");
    window_.create("Arider", screen_width_, screen_height_, yage::WindowFlags::SHOWN);
    initShaders();

    player_.create(glm::vec2(0.f, 0.f), glm::vec2(66, 92), glm::vec2(5.f, 5.f));
    player_.animation_.pushFrame("idle", "res/textures/Player/p3_front.png");
    for(int i=1; i<=11; ++i)
    {
	if(i<10)
	{
	    player_.animation_.pushFrame("move", "res/textures/Player/p3_walk/PNG/p3_walk0"+std::to_string(i)+".png");
	}
	else
	{
	    player_.animation_.pushFrame("move", "res/textures/Player/p3_walk/PNG/p3_walk"+std::to_string(i)+".png");
	}
    }
}

void Game::initShaders()
{
    program_.compileShaders("res/shaders/color_shading.vert", "res/shaders/color_shading.frag");
    program_.addAttribute("vertex_position");
    program_.addAttribute("vertex_color");
    program_.addAttribute("vertex_uv");
    program_.linkShaders();
}

void Game::processInput()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
	switch(event.type)
	{
	case SDL_QUIT:
	    game_state_=GameState::EXIT;
	    break;
	case SDL_KEYDOWN:
	    input_manager_.keyPressed(event.key.keysym.sym);
	    break;
	case SDL_KEYUP:
	    input_manager_.keyReleased(event.key.keysym.sym);
	}
    }

    player_.animation_.start("idle");
    player_.idle();

    if(input_manager_.isKeyPressed(SDLK_w))
    {	
	player_.animation_.start("idle");
	player_.moveUp();
    }
    if(input_manager_.isKeyPressed(SDLK_s))
    {	
	player_.animation_.start("idle");
	player_.moveDown();
    }
    if(input_manager_.isKeyPressed(SDLK_d))
    {	
	player_.animation_.start("move");
	player_.moveRight();
    }
    if(input_manager_.isKeyPressed(SDLK_a))
    {
	player_.animation_.start("move");
	player_.moveLeft();
    }

    if(time_%3==0)
	player_.animation_.nextFrame();
}

void Game::gameLoop()
{    
    while(game_state_!=GameState::EXIT)
    {
	processInput();
	drawGame();
	time_+=1;
    }
}

void Game::drawGame()
{
    window_.clearBuffer();
    
    program_.use();
    camera_.update(program_);

    // activate texture 0
    glActiveTexture(GL_TEXTURE0);
    // bind it to the sampler
    GLint texture_location=program_.getUniformLocation("texture_sampler");
    glUniform1i(texture_location, 0);

    // GLint time_location = program_.getUniformLocation("time");
    // glUniform1f(time_location, time_);
    
    renderSprites();

    glBindTexture(GL_TEXTURE_2D, 0);
    program_.unuse();

    // swap buffer and draw everything to the screen
    window_.swapBuffer();
}

void Game::renderSprites()
{
    // draw the sprite batches
    sprite_batch_.begin();

    // drawing the player
    player_.renderSprite(sprite_batch_);

    // drawing the background
    sprite_batch_.draw(glm::vec4(0.f, 0.f, 2560, 2560), glm::vec4(0.f, 0.f, 10.f, 10.f), yage::ResourceManager::getTexture("res/textures/bg_castle.png").id, yage::Color(255, 255, 255, 255), -1.f);

    sprite_batch_.end();
    sprite_batch_.render();    
}

float Game::calculateFps()
{
    static const int NUM_SAMPLES = 100;
    static float frame_times[NUM_SAMPLES];
    static float prev_ticks = SDL_GetTicks();
    static unsigned current_frame = 0;

    float current_ticks = SDL_GetTicks();

    frame_times[current_frame%NUM_SAMPLES] = current_ticks-prev_ticks;
    prev_ticks = current_ticks;

    int count = NUM_SAMPLES;
    if(current_frame<NUM_SAMPLES)
	count = current_frame;

    float frame_time_average = 0;
    for(int i = 0; i < count; ++i)
	frame_time_average += frame_times[i];
    frame_time_average /= count;

    float fps = 60.f;
    if(frame_time_average>0)
	fps = 1000.f/frame_time_average;

    ++current_frame;

    return fps;
}
