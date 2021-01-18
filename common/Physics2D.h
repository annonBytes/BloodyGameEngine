
#pragma once

#include <EntityService.h>
#include <Vector2.h>

class Physics2D : public astu::EntityComponent
{
public:
    Physics2D(double velX = 0, double velY = 0, double forceX = 0, double forceY = 0, double _mass = 0);
        :vel(velX, velY),
         force(forceX, forceY),
         mass(_mass)
        {
            //intentionally left empty
        }

        Physics2D(const astu::Vector2<double> &v, const astu::Vector2<double> &f, double _mass = 0)
            : vel(v),
              force(f),
              mass(_mass)
        {
            //intentionally left empty
        }
};
