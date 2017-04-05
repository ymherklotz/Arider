#include "game.hpp"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include <YAGE/gltexture.hpp>
#include <YAGE/resourcemanager.hpp>
#include <YAGE/vertex.hpp>

#include <stdexcept>
#include <iostream>

Game::Game(int screen_width/*=1280*/, int screen_height/*=720*/) :
    screen_width_(screen_width),
    screen_height_(screen_height),
    window_(),
    camera_(screen_width_, screen_height_),
    program_(),
    sprite_batch_()
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

    static const float CAMERA_SPEED = 5.f;
    // static const float SCALE_SPEED = 0.1f;

    while(SDL_PollEvent(&event))
    {
	switch(event.type)
	{
	case SDL_QUIT:
	    game_state_ = GameState::EXIT;
	    break;
	case SDL_MOUSEMOTION:
	    // when mouse moves
	    break;
	case SDL_KEYDOWN:
	    input_manager_.keyPressed(event.key.keysym.sym);
	    break;
	case SDL_KEYUP:
	    input_manager_.keyReleased(event.key.keysym.sym);
	}
    }

    if(input_manager_.isKeyPressed(SDLK_w))
	camera_.move(glm::vec2(0, CAMERA_SPEED));
    if(input_manager_.isKeyPressed(SDLK_d))
	camera_.move(glm::vec2(CAMERA_SPEED, 0));
    if(input_manager_.isKeyPressed(SDLK_s))
	camera_.move(glm::vec2(0, -CAMERA_SPEED));
    if(input_manager_.isKeyPressed(SDLK_a))
	camera_.move(glm::vec2(-CAMERA_SPEED, 0));    
}

void Game::gameLoop()
{    
    while(game_state_ != GameState::EXIT)
    {
	processInput();
	drawGame();
	time_ += 0.05;
	// std::cout<<calculateFps()<<'\n';
    }
}

void Game::drawGame()
{
    window_.clearBuffer();
    
    program_.use();
    camera_.update();
    
    glActiveTexture(GL_TEXTURE0);   
    GLint texture_location = program_.getUniformLocation("texture_sampler");
    glUniform1i(texture_location, 0);

    // GLint time_location = program_.getUniformLocation("time");
    // glUniform1f(time_location, time_);

    GLint matrix_location = program_.getUniformLocation("P");
    glUniformMatrix4fv(matrix_location, 1, GL_FALSE, &(camera_.getCameraMatrix()[0][0]));
    
    // draw the sprite batches
    sprite_batch_.begin();

    glm::vec4 rect(200.f, 200.f, 66.f, 92.f);
    glm::vec4 uv(0.f, 0.f, 1.f, 1.f);
    yage::GlTexture texture=yage::ResourceManager::getTexture("res/textures/Player/p1_front.png");
    yage::Color color;
    color.r=255;
    color.g=255;
    color.b=255;
    color.a=255;
    sprite_batch_.draw(rect, uv, texture.id, color, 0.f);
    sprite_batch_.end();
    sprite_batch_.render();

    glBindTexture(GL_TEXTURE_2D, 0);
    program_.unuse();

    // swap buffer and draw everything to the screen
    window_.swapBuffer();
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
