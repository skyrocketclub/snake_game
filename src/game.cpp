#include "game.h"
#include <iostream>
#include "SDL.h"
#include <fstream>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    //add two arguments bool surpass & int score
    //surpass indicates if you pass the highscore & score is now your new score...
    renderer.Render(snake, food,surpass, score);
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      h_score = GetH_Score();
      renderer.UpdateWindowTitle(score, frame_count,h_score);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }

}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive){
    //check if he beat the highscore, if yes, surpass = true
    checkHighScore(score);
    return;
  }

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.01;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
int Game::GetH_Score() {
  std::ifstream in_file;
  in_file.open("highscore.txt");
  if(!in_file){
    std::cout<<"No Current Highscore\n";

    //meaning the file is not yet in existence
    std::ofstream out_file;
    out_file.open("highscore.txt",std::ios::out);
    out_file<<0;
    h_score = 0;
    out_file.close();
  }
  else{
    in_file>>h_score;
    in_file.close();
  }
  return h_score;
}

void Game::checkHighScore(int score){
  int c_highscore{};
  std::ifstream in_file;
  in_file.open("highscore.txt");

    if(!in_file){
    std::cout<<"Unable to fetch current high score...\n";
    }
    else{
      in_file>>c_highscore;
      if(score>c_highscore){
        //call function to update the new highscore...
        in_file.close();
        surpass = true;
        updateHighScore(score); 
        return;
      }
      else{
          // std::cout<<"Unable to beat High score, try again!\n";
      }
    }

  in_file.close();
}

void Game::updateHighScore(int score){
 //record the new score ...
  std::ofstream out_file;
  out_file.open("highscore.txt",std::ios::out);
  out_file<<score;
  out_file.close();
}