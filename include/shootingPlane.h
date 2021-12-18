#ifndef SHOOTINGPLANE_H
#define SHOOTINGPLANE_H

#include <vector>
#include "SDL.h"
#include "targetObj.h"

class ShootingPlane {
 public:
  // enum class Direction { kUp, kDown, kLeft, kRight, kSpace, kEmpty };
  enum class Direction { kLeft, kRight, kSpace, kEmpty };

  ShootingPlane(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        headX(grid_width/2),
        headY(grid_height-1){}

  void Update();

  Direction direction = Direction::kEmpty;

  float speed{1.0f};
  int size{1};
  bool alive{true};
  float headX;
  float headY;
  std::vector<SDL_Point> body;
  std::vector<TargetObj> bullets;


 private:
  void UpdateKeys();
  void UpdateBodyPlane();

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif