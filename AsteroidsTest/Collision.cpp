#include "Collision.h"
#include "Collider.h"
#include "Game.h"
#include <functional>

Collision::Collision()
{
}

Collision::~Collision()
{
	for (ColliderList::iterator colliderIt = colliders_.begin(), end = colliders_.end();
		colliderIt != end;
		++colliderIt)
	{
		delete *colliderIt;
	}
}

Collider *Collision::CreateCollider(GameEntity *entity)
{
	Collider *collider = new Collider();

	collider->position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	collider->radius = 0.0f;
	collider->entity = entity;
	collider->enabled = true;
	colliders_.push_back(collider);

	return collider;
}

void Collision::DestroyCollider(Collider *collider)
{
	colliders_.remove_if(std::bind1st((std::equal_to<Collider *>()), collider));
	delete collider;
}

void Collision::UpdateColliderPosition(Collider *collider, const D3DXVECTOR3 &position)
{
	collider->position = position;
}

void Collision::UpdateColliderRadius(Collider *collider, float radius)
{
	collider->radius = radius;
}

void Collision::EnableCollider(Collider *collider)
{
	collider->enabled = true;
}

void Collision::DisableCollider(Collider *collider)
{
	collider->enabled = false;
}

void Collision::DoCollisions(Game *game) const
{
	bool collided = false;
	for (ColliderList::const_iterator colliderAIt = colliders_.begin(), end = colliders_.end();
		colliderAIt != end;
		++colliderAIt)
	{
		ColliderList::const_iterator colliderBIt = colliderAIt;
		for (++colliderBIt; colliderBIt != end; ++colliderBIt)
		{
			Collider *colliderA = *colliderAIt;
			Collider *colliderB = *colliderBIt;
			if (CollisionTest(colliderA, colliderB))
			{
				game->DoCollision(colliderA->entity, colliderB->entity);
				collided = true;
				break;
			}
		}
		if (collided)
		{
			collided = false;
			break;
		}
	}
}

bool Collision::CollisionTest(Collider *a, Collider *b)
{
	if (a->enabled == false)
		return false;
	if (b->enabled == false)
		return false;

	D3DXVECTOR3 diff;
	D3DXVec3Subtract(&diff, &a->position, &b->position);
	float distance = D3DXVec3Length(&diff);
	if (distance < (a->radius + b->radius))
	{
		return true;
	}

	return false;
}
