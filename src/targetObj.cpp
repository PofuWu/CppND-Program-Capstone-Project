#include "targetObj.h"
#include <iostream>
TargetObj::TargetObj(){}

TargetObj::TargetObj(int x, int y){
    targetX = x;
    targetY = y;
}

void TargetObj::placeTarget(int x, int y){
    targetX = x;
    targetY = y;
}

void TargetObj::setSpeed(float speed){
    targetSpeed = speed;
}

void TargetObj::speedIncrease(){
    targetSpeed += 0.1;
}

void TargetObj::updateTarget(TargetDirection targetDirection){
    if(targetDirection == TargetDirection::UP)
        targetY -= targetSpeed;
    else
        targetY += targetSpeed;
}


SDL_Point TargetObj::getTarget2D() const{

    SDL_Point target2D{static_cast<int>(targetX), static_cast<int>(targetY)}; 
    
    return target2D;
}