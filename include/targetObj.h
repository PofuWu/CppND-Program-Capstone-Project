#ifndef TARGETOBJ_H
#define TARGETOBJ_H
#include "SDL.h"
#include <vector>

class TargetObj{
 public:
    enum class TargetDirection { UP, DOWN };
    TargetObj();
    TargetObj(int x, int y);

    float targetSpeed{0.1f};
    SDL_Point getTarget2D() const;
    bool targetReady{false};
    bool targetActive{false};

    void placeTarget(int x, int y);
    void setSpeed(float speed);
    void speedIncrease();
    void updateTarget(TargetDirection targetDirection);

 private:
    float targetX;
    float targetY;
};

#endif