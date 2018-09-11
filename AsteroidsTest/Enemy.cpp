#include "Enemy.h"
#include "Graphics.h"
#include "Random.h"
#include "Maths.h"
#include "Ship.h"

Enemy::Enemy(const D3DXVECTOR3 &position,
	const D3DXVECTOR3 &velocity,
	Ship *target) :
	velocity_(velocity),
	angle_(0.0f)
{
	SetPosition(position);
	targetShip = target;
}

void Enemy::Update(System *system)
{
	D3DXVECTOR3 position = GetPosition();

	D3DXVec3Subtract(&velocity_, &GetPosition(), &targetShip->GetPosition());
	D3DXVec3Normalize(&velocity_, &velocity_);
	velocity_ *= -1;

	D3DXVec3Add(&position, &position, &velocity_);
	SetPosition(position);

}

void Enemy::Render(Graphics *graphics) const
{
	struct DummyVert
	{
		float x, y, z;
		D3DCOLOR diffuse;
	};

	DummyVert axis[8] =
	{
		{ 0.0f, -7.0f, 0.0f, 0xffffffff },{ 0.0f, 15.0f, 0.0f, 0xffffffff },
	{ -7.0f, 0.0f, 0.0f, 0xffff00ff },{ 7.0f, 0.0f, 0.0f, 0xffff00ff },
	{ 0.0f, 15.0f, 0.0f, 0xffff00ff },{ -7.0f, 7.0f, 0.0f, 0xffff00ff },
	{ 0.0f, 15.0f, 0.0f, 0xffff00ff },{ 7.0f, 7.0f, 0.0f, 0xffff00ff },
	};

	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationZ(&rotationMatrix, angle_);

	D3DXVECTOR3 position = GetPosition();
	D3DXMATRIX translationMatrix;
	D3DXMatrixTranslation(&translationMatrix,
		position.x,
		position.y,
		position.z);

	D3DXMATRIX shipTransform = rotationMatrix * translationMatrix;

	D3DXMATRIX identityMatrix;
	D3DXMatrixIdentity(&identityMatrix);

	DWORD dummyFvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	graphics->SetVertexFormat(dummyFvf);
	graphics->DisableLighting();
	graphics->SetModelMatrix(&shipTransform);
	graphics->DrawImmediate(D3DPT_LINELIST,
		4,
		&axis[0],
		sizeof(axis[0]));
	graphics->SetModelMatrix(&identityMatrix);
	graphics->EnableLighting();

}

D3DXVECTOR3 Enemy::GetVelocity() const
{
	return velocity_;
}

int Enemy::GetSize() const
{
	return size_;
}
