#include "GameEntity.h"
#include "Collision.h"

GameEntity::GameEntity() :
	position_(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	collisionSystem_(0),
	collider_(0)
{
}

GameEntity::~GameEntity()
{
	DestroyCollider();
}

void GameEntity::Update(System *system)
{
}

void GameEntity::Render(Graphics *graphics) const
{
}

D3DXVECTOR3 GameEntity::GetPosition() const
{
	return position_;
}

void GameEntity::SetPosition(const D3DXVECTOR3 &position)
{
	position_ = position;
	if (HasValidCollider())
	{
		collisionSystem_->UpdateColliderPosition(collider_, position_);
	}
}

void GameEntity::EnableCollisions(Collision *collisionSystem, float radius)
{
	DestroyCollider();

	collisionSystem_ = collisionSystem;
	collider_ = collisionSystem_->CreateCollider(this);
	collisionSystem_->UpdateColliderPosition(collider_, position_);
	collisionSystem_->UpdateColliderRadius(collider_, radius);
}

void GameEntity::DisableCollisions()
{
	DestroyCollider();
}

bool GameEntity::HasValidCollider() const
{
	return collisionSystem_ && collider_;
}

void GameEntity::DestroyCollider()
{
	if (HasValidCollider())
	{
		collisionSystem_->DestroyCollider(collider_);
	}

	collisionSystem_ = 0;
	collider_ = 0;
}
