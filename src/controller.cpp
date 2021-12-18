#include "controller.h"
#include <iostream>
#include "SDL.h"

void Controller::ChangeDirection(ShootingPlane &shootingPlane, ShootingPlane::Direction input,
                                 ShootingPlane::Direction opposite) const {
  if (shootingPlane.direction != opposite || shootingPlane.size == 1) shootingPlane.direction = input;
  return;
}

void Controller::HandleInput(bool &running, ShootingPlane &shootingPlane) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        // case SDLK_UP:
        //   ChangeDirection(shootingPlane, ShootingPlane::Direction::kUp,
        //                   ShootingPlane::Direction::kDown);
        //   break;

        // case SDLK_DOWN:
        //   ChangeDirection(shootingPlane, ShootingPlane::Direction::kDown,
        //                   ShootingPlane::Direction::kUp);
        //   break;

        case SDLK_LEFT:
          ChangeDirection(shootingPlane, ShootingPlane::Direction::kLeft,
                          ShootingPlane::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(shootingPlane, ShootingPlane::Direction::kRight,
                          ShootingPlane::Direction::kLeft);
          break;
        
        case SDLK_SPACE:
          shootingPlane.direction = ShootingPlane::Direction::kSpace;
          break;
      }
    }
  }
}