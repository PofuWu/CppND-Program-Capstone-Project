#include "game.h"
#include <iostream>
#include "SDL.h"
#include <algorithm>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : shootingPlane(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  // Initialize the first target with specific speed.
  TargetObj target(random_w(engine), 0);
  targets.emplace_back(target);
  phaseSpeed = target.targetSpeed;
  

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, shootingPlane);
    Update();
    renderer.Render(shootingPlane, targets);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
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


void Game::setPhaseSpeed(){
  if (score % phaseThres == 0 && score > 0){
    phaseThres += 5;
    std::cout << "Target Speed Up." << std::endl;
    phaseSpeed += 0.05;
  }
}

void Game::checkTargetBottom(){
  for (auto& target : targets){
    if(target.getTarget2D().y >= static_cast<int>(shootingPlane.headY) && target.getTarget2D().x != static_cast<int>(shootingPlane.headX)){
        target.placeTarget(random_w(engine), 0);
    }
  }
}

void Game::spawnTarget(){
  if(targets.empty()){
    TargetObj target(random_w(engine), 0);
    setPhaseSpeed();
    target.setSpeed(phaseSpeed);
    targets.emplace_back(target);
  }
}

void Game::checkTargetMatch(){
  int countBullet = 0;
  if(shootingPlane.bullets.size() > 0 && targets.size() > 0)
  {
    for (auto bullet : shootingPlane.bullets){
      if(targets.size()>0){
        int countTarget = 0;
        for (auto target : targets){
          if(bullet.getTarget2D().x == target.getTarget2D().x && bullet.getTarget2D().y == target.getTarget2D().y){
            score++;
            std::cout << score << std::endl;
            shootingPlane.bullets.erase(shootingPlane.bullets.begin() + countBullet);
            targets.erase(targets.begin() + countTarget);
            countBullet--;
            countTarget--;
          }
          countTarget++;
        }
      }
      countBullet++;
    }
  }
}

bool Game::checkPlaneAlive(){
  if(targets.size() > 0){
    for (auto target : targets){
      if (static_cast<int>(shootingPlane.headX) == target.getTarget2D().x && static_cast<int>(shootingPlane.headY) == target.getTarget2D().y)
        return true;
    }
  }
  return false;
}

void Game::Update() {
  if (checkPlaneAlive()){
    shootingPlane.alive = false;
    return;
  }

  shootingPlane.Update();
  checkTargetMatch();
  for (auto& target : targets)
    target.updateTarget(TargetObj::TargetDirection::DOWN);
  spawnTarget();
  checkTargetBottom();
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return shootingPlane.size; }