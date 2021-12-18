#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "shootingPlane.h"
#include "targetObj.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  //void Render(ShootingPlane const &shootingPlane, SDL_Point const &food);
  void Render(ShootingPlane const &shootingPlane, std::vector<TargetObj> const targets);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif