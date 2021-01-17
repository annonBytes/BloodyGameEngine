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

#define ENTITY_RADIUS 15.0
#define NUM_ENTITIES 10

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

// void PlayerTestService::OnUpdate()
// {
//     Mouse mouse;
//     Vector2<double> pos(mouse.GetCursorX(), mouse.GetCursorY());
//     std::cout << pos << std::endl;
// }

void PlayerTestService::ProcessEntity(Entity &e)
{

    Mouse mouse;
    Vector2<double> pos(mouse.GetCursorX(), mouse.GetCursorY());

    auto &pose = e.GetComponent<Pose2D>();
    if (pose.pos.x - pos.x < 20 && pose.pos.y - pos.y < 20 && pose.pos.x - pos.x > -20 && pose.pos.y - pos.y > -20)
    {
        pose.pos.x += 20;
        pose.pos.y += 20;
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

void PlayerTestService::OnSignal(const astu::MouseButtonEvent &signal)
{
}
