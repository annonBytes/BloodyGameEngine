#pragma once

#include <UpdateService.h>
#include <EntityService.h>
#include <SignalService.h>
#include "CircleCollider.h"

class Player : public astu::EntityComponent
{
public:
    Player(float p_x, float p_y, astu::Vector2<CircleCollider> p_tex);
    float distanceFromCursor();
    const char *getScore();
    const char *getHighscore();
    bool jump();
    void reset();
    int isDead();
    int getScoreInt();

private:
    float velocityX, velocityY;
    int score = 0;
    int highscore = 0;
    int timer = 0;
    int dead = 0;
};