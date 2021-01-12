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
#include <Mouse.h>
#include "IWindowManager.h"
#include "Pose2D.h"
#include "Player.h"
#include "LinearMovement.h"
#include "CollisionTestService.h"
#include "PlayerTestService.h"

#define ENTITY_RADIUS 15.0
#define NUM_ENTITIES 50

using namespace astu;

PlayerTestService::PlayerTestService(int priority) : UpdatableBaseService("playerTest", priority)
{
}

void PlayerTestService::OnStartup(/* args */)
{
    GetSM().GetService<MouseButtonEventService>().AddListener(shared_as<PlayerTestService>());
}

void PlayerTestService::OnShutdown()
{
    GetSM().GetService<MouseButtonEventService>().RemoveListener(shared_as<PlayerTestService>());
}

void PlayerTestService::OnUpdate()
{
    Mouse mouse;
    Vector2<double> pos(mouse.GetCursorX(), mouse.GetCursorY());
    std::cout << pos << std::endl;
}

void PlayerTestService::OnSignal(const astu::MouseButtonEvent &signal)
{
}
