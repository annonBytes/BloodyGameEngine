#include <stdexcept>
#include <EntityService.h>
#include <Vector2.h>
#include <iostream>

#include "Pose2D.h"
#include "Player.h"
#include "PlayerMoveSystem.h"

using namespace astu;

PlayerMoveSystem::PlayerMoveSystem(int priority)
    : UpdatableBaseService("Player Move", priority)
{
    // Intentionally left empty.
}

void PlayerMoveSystem::OnStartup()
{
    auto &es = GetSM().GetService<EntityService>();
    entityView =
        es.GetEntityView(EntityFamily::Create<Pose2D, Player>());

    playerEventService = GetSM().FindService<PlayerEventService>();
    if (!playerEventService)
    {
        throw std::logic_error("Player system requires player event service");
    }
}

void PlayerMoveSystem::OnShutdown()
{
    playerEventService = nullptr;
    entityView = nullptr;
}

void PlayerMoveSystem::OnUpdate()
{
    for (size_t j = 0; j < entityView->size(); ++j)
    {
        const auto &entityA = (*entityView)[j];

        for (size_t i = j + 1; i < entityView->size(); ++i)
        {
            const auto &entityB = (*entityView)[i];

            if (IsMoving(*entityA, *entityB))
            {
                DistanceFromCursor(entityA, entityB);
            }
        }
    }
}

bool PlayerMoveSystem::IsMoving(astu::Entity &a, astu::Entity &b)
{
    // Get components of entity A
    auto &poseA = a.GetComponent<Pose2D>();
    auto &colA = a.GetComponent<Player>();

    // Get components of entity B
    auto &poseB = b.GetComponent<Pose2D>();
    auto &colB = b.GetComponent<Player>();

    Vector2<double> d = poseA.pos - poseB.pos;

    double radiusSum = colA.radius + colB.radius;
    return d.LengthSquared() <= radiusSum * radiusSum;
}

void PlayerMoveSystem::DistanceFromCursor(std::shared_ptr<astu::Entity> a, std::shared_ptr<astu::Entity> b)
{
    playerEventService->QueueSignal(PlayerEvent(a, b));
}