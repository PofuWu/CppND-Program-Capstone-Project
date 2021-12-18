#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "shootingPlane.h"

class Controller {
 public:
  void HandleInput(bool &running, ShootingPlane &ShootingPlane) const;

 private:
  void ChangeDirection(ShootingPlane &ShootingPlane, ShootingPlane::Direction input,
                       ShootingPlane::Direction opposite) const;
};

#endif