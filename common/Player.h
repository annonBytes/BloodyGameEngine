#pragma once

#include <EntityService.h>
#include <Vector2.h>

class Player : public astu::EntityComponent
{
public:
    /** The radius of the circle collider. */
    double radius;

    /**
     * Constructor.
     * 
     * @param r the radius
     */
    Player(double r = 1.0)
        : radius(r)
    {
        // Intentionally left empty.
    }

    //     Player(float p_x, float p_y, astu::Vector2<CircleCollider> p_tex);
    //     float distanceFromCursor();
    //     const char *getScore();
    //     const char *getHighscore();
    //     bool jump();
    //     void reset();
    //     int isDead();
    //     int getScoreInt();

    // private:
    //     float velocityX, velocityY;
    //     int score = 0;
    //     int highscore = 0;
    //     int timer = 0;
    //     int dead = 0;
};
