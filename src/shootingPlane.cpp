#include "shootingPlane.h"
#include <cmath>
#include <iostream>

void ShootingPlane::Update() {

  UpdateKeys();

  if(!bullets.empty()){
    for (auto& bullet : bullets){
      if (bullet.targetReady){  
        bullet.placeTarget(static_cast<int>(headX),static_cast<int>(headY)-1);
        bullet.targetReady = false;
        bullet.targetActive = true;
      }
      else if (bullet.targetActive){
        bullet.updateTarget(TargetObj::TargetDirection::UP);
      }
    }
  }
  UpdateBodyPlane();
}

void ShootingPlane::UpdateKeys() {
  switch (direction) {
    case Direction::kLeft:
      headX -= speed;
      direction = Direction::kEmpty;
      break;

    case Direction::kRight:
      headX += speed;
      direction = Direction::kEmpty;
      break;
    case Direction::kSpace:{ // should use {} if the statement more than 2 lines.
      TargetObj bullet(headX, headY-1);
      bullet.targetReady = true;
      bullets.emplace_back(bullet);
      direction = Direction::kEmpty;
      break;
      }
    case Direction::kEmpty:
      break;
  }

  // Wrap the ShootingPlane around to the beginning if going off of the screen.
  headX = fmod(headX + grid_width, grid_width);
  headY = fmod(headY + grid_height, grid_height);
}


void ShootingPlane::UpdateBodyPlane(){
  body.clear();
  SDL_Point PlaneLeft{static_cast<int>(headX - 1), static_cast<int>(headY)};
  SDL_Point PlaneRight{static_cast<int>(headX + 1), static_cast<int>(headY)};
  body.emplace_back(PlaneLeft);
  body.emplace_back(PlaneRight);
}
