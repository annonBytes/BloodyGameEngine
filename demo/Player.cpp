#include <Vector2.h>
#include <iostream>
#include <Vector2.h>
#include <EntityService.h>
#include <cmath>
#include <string>
#include <Mouse.h>
#include <Events.h>
#include "player.h"
#include "CircleCollider.h"

const float GRAVITY = 0.09f;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
const int ALIVE = 0;
const int CURSOR_DEATH = 1;
const int HOLE_DEATH = 2;

Player::Player(float p_x, float p_y, astu::Vector2<CircleCollider> p_tex)
    : Entity{p_x, p_y, p_tex}
{
    setX(SCREEN_WIDTH / 2 - getWidth() / 2);
    setY(SCREEN_HEIGHT - getHeight() - 64);
}

float Player::distanceFromCursor()
{
    int mouseX = 0;
    int mouseY = 0;

    return sqrt(pow((getX() + getWidth() / 2) - mouseX, 2) + pow((getY() + getHeight() / 2) - mouseY, 2));
}

bool Player::jump()
{
    if (distanceFromCursor() < 100)
    {
        velocityY = -(1 / distanceFromCursor() * 200);
        return true;
    }

    return false;
}

float Player::clamp(float p_value, float p_min, float p_max)
{
    if (p_value > p_max)
        return p_max;
    if (p_value < p_min)
        return p_min;
    return p_value;
}

int Player::getScoreInt()
{
    return score;
}

int Player::isDead()
{
    return dead;
}