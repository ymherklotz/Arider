#include "game.hpp"

#include <YAGE/sprite.hpp>

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
    sprites_.push_back(std::make_shared<yage::Sprite>());
    sprites_.back()->init(0.f, 0.f, 66.f, 92.f, "res/platformer_png/Player/p1_stand.png");
    sprites_.push_back(std::make_shared<yage::Sprite>());
    sprites_.back()->init(100.f, 0.f, 66.f, 92.f, "res/platformer_png/Player/p2_jump.png");
    sprites_.push_back(std::make_shared<yage::Sprite>());
    sprites_.back()->init(200.f, 0.f, 66.f, 92.f, "res/platformer_png/Player/p3_jump.png");
    
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

    static const float CAMERA_SPEED = 20.f;
    static const float SCALE_SPEED = 0.1f;

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

	    break;
	}
    }
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
    glClearDepth(1.0);
    // clears buffer with clear color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    program_.use();
    camera_.update();
    glActiveTexture(GL_TEXTURE0);
    
    GLint texture_location = program_.getUniformLocation("texture_sampler");
    glUniform1i(texture_location, 0);

    // GLint time_location = program_.getUniformLocation("time");
    // glUniform1f(time_location, time_);

    GLint matrix_location = program_.getUniformLocation("P");
    glUniformMatrix4fv(matrix_location, 1, GL_FALSE, &(camera_.getCameraMatrix()[0][0]));
    
    for(auto sprite : sprites_)
	sprite->draw();

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
