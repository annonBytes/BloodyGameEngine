/*  ____          _____          _____          
 * |  _ \   /\   / ____|   /\   / ____|   /\    
 * | |_) | /  \ | |  __   /  \ | |  __   /  \   
 * |  _ < / /\ \| | |_ | / /\ \| | |_ | / /\ \  
 * | |_) / ____ \ |__| |/ ____ \ |__| |/ ____ \ 
 * |____/_/    \_\_____/_/    \_\_____/_/    \_\
 *
 * Bagaga - Bloody Amazing Game Architecture Game
 * Copyright 2020 Bagaga Development Team. All rights reserved.                                             
 */

#define _USE_MATH_DEFINES
#include <cmath>
#include <typeindex>
#include <typeinfo>
#include <iostream>
#include <AstUtils.h>
#include <EntityService.h>
#include "IWindowManager.h"
#include "Pose2D.h"
#include "Mouse.h"
#include "LinearMovement.h"
#include "PlayerTestService.h"
#include "Player.h"
#include "PlayerMoveSystem.h"
#include "CollisionTestService.h"
#include "CollisionDetectionSystem.h"

#define ENTITY_RADIUS 15.0
#define NUM_ENTITIES 5

using namespace astu;

const EntityFamily PlayerTestService::FAMILY = EntityFamily::Create<Pose2D, Polyline>();

PlayerTestService::PlayerTestService(int priority) : IteratingEntitySystem(FAMILY, priority, "Player Visual System")
{

    // Create circular shape.
    const int nSegments = 15;
    shape2 = std::make_shared<Polyline::Polygon>();

    double da = (2 * M_PI) / nSegments;
    for (int i = 0; i < nSegments; ++i)
    {
        Vector2<double> v(ENTITY_RADIUS, 0);
        v.Rotate(da * i);
        shape2->push_back(v);
    }
}

void PlayerTestService::OnStartup(/* args */)
{
    GetSM().GetService<MouseButtonEventService>().AddListener(shared_as<PlayerTestService>());

    auto &wm = GetSM().GetService<IWindowManager>();

    for (int i = 0; i < NUM_ENTITIES; ++i)
    {
        Vector2<double> p;
        p.x = GetRandomDouble(ENTITY_RADIUS, wm.GetWidth() - ENTITY_RADIUS);
        p.y = GetRandomDouble(ENTITY_RADIUS, wm.GetHeight() - ENTITY_RADIUS);

        AddTestEntity(p, GetRandomDouble(-180, 180), WebColors::White);
    }
}

void PlayerTestService::OnShutdown()
{
    GetSM().GetService<MouseButtonEventService>().RemoveListener(shared_as<PlayerTestService>());
}

void PlayerTestService::ProcessEntity(Entity &e)
{

    auto &wm = GetSM().GetService<astu::IWindowManager>();
    width = wm.GetWidth();
    height = wm.GetHeight();

    Mouse mouse;
    Vector2<double> pos(mouse.GetCursorX(), mouse.GetCursorY());

    auto &pose = e.GetComponent<Pose2D>();
    auto &mov = e.GetComponent<LinearMovement>();

    // pose.pos += mov.vel * GetDeltaTime();

    // Keep within boundaries.
    if (pose.pos.x < 0)
    {
        pose.pos.x = 0;
        mov.vel.x = -mov.vel.x;
    }
    if (pose.pos.x >= width)
    {
        pose.pos.x = width - 1;
        mov.vel.x = -mov.vel.x;
    }

    if (pose.pos.y < 0)
    {
        pose.pos.y = 0;
        mov.vel.y = -mov.vel.y;
    }
    if (pose.pos.y >= height)
    {
        pose.pos.y = height - 1;
        mov.vel.y = -mov.vel.y;
    }

    if (pose.pos.x - pos.x < 20 && pose.pos.y - pos.y < 20 && pose.pos.x - pos.x > -20 && pose.pos.y - pos.y > -20)
    {
        // pose.pos.x -= 50;
        // pose.pos.y -= 50;

        // pose.pos.x = pose.pos.x + mov.vel.x;
        // pose.pos.y = pose.pos.y + mov.vel.y;
        pose.pos.x = pos.x - mov.vel.x * GetDeltaTime();
        mov.vel.x = mov.vel.x - pose.pos.x * GetDeltaTime();

        pose.pos.y = pos.y - mov.vel.y * GetDeltaTime();
        mov.vel.y = mov.vel.y - pose.pos.y * GetDeltaTime();
    }
}

void PlayerTestService::AddTestEntity(const Vector2<double> &p, double s, const Color &c)
{
    Vector2<double> v(GetRandomDouble(50, 200), 0);
    v.Rotate(ToRadians(GetRandomDouble(0, 360)));

    auto entity = std::make_shared<Entity>();
    entity->AddComponent(std::make_shared<Pose2D>(p));
    entity->AddComponent(std::make_shared<Polyline>(shape2, c));
    entity->AddComponent(std::make_shared<LinearMovement>(v));
    entity->AddComponent(std::make_shared<Player>(ENTITY_RADIUS));

    auto &es = GetSM().GetService<EntityService>();
    es.AddEntity(entity);
}

bool PlayerTestService::IsColliding(astu::Entity &a, astu::Entity &b)
{
    // Get components of entity A
    auto &poseA = a.GetComponent<Pose2D>();
    auto &colA = a.GetComponent<CircleCollider>();

    // Get components of entity B
    auto &poseB = b.GetComponent<Pose2D>();
    auto &colB = b.GetComponent<CircleCollider>();

    Vector2<double> d = poseA.pos - poseB.pos;

    double radiusSum = colA.radius + colB.radius;
    return d.LengthSquared() <= radiusSum * radiusSum;
}

void PlayerTestService::OnSignal(const astu::MouseButtonEvent &signal)
{
}
