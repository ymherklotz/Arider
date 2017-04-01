#include "game.hpp"
#include "sprite.hpp"

#include <stdexcept>
#include <iostream>

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

    // SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    // SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


    window_ = SDL_CreateWindow("Arider", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			       width_, height_, SDL_WINDOW_OPENGL);
    if(window_ == nullptr)
	throw std::runtime_error("SDL_CreateWindow failed");

    SDL_GLContext gl_context = SDL_GL_CreateContext(window_);
    if(gl_context == nullptr)
	throw std::runtime_error("SDL_GL_CreateContext failed");

    GLenum error = glewInit();
    if(error != GLEW_OK)
	throw std::runtime_error("glewInit failed");

    std::cout<<"***  OpenGL version: "<<glGetString(GL_VERSION)<<"  ***\n";

    SDL_GL_SetSwapInterval(1);

    glClearColor(0.f, 0.f, 0.f, 1.f);

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
    glActiveTexture(GL_TEXTURE0);
    
    GLint texture_location = program_.getUniformLocation("texture_sampler");
    glUniform1i(texture_location, 0);

    GLint time_location = program_.getUniformLocation("time");
    glUniform1f(time_location, time_);
    
    for(auto sprite : sprites_)
	sprite->draw();

    glBindTexture(GL_TEXTURE_2D, 0);
    program_.unuse();

    // swap buffer and draw everything to the screen
    SDL_GL_SwapWindow(window_);
}

void Game::run()
{
    initSystems();
    sprites_.push_back(std::make_shared<Sprite>());
    sprites_.back()->init(-1.f, -1.f, 1.f, 1.f, "res/platformer_png/Player/p1_stand.png");
    sprites_.push_back(std::make_shared<Sprite>());
    sprites_.back()->init(0.f, -1.f, 1.f, 1.f, "res/platformer_png/Player/p1_jump.png");
    sprites_.push_back(std::make_shared<Sprite>());
    sprites_.back()->init(0.f, 0.f, 1.f, 1.f, "res/platformer_png/Player/p1_hurt.png");
    sprites_.push_back(std::make_shared<Sprite>());
    sprites_.back()->init(-1.f, 0.f, 1.f, 1.f, "res/platformer_png/Player/p1_duck.png");    
    gameLoop();
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
