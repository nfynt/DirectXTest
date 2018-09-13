#include "Bullet.h"
#include "Graphics.h"

Bullet::Bullet(const D3DXVECTOR3 &position,
	const D3DXVECTOR3 &direction)
{
	const float BULLET_SPEED = 4.0f;

	SetPosition(position);
	D3DXVECTOR3 normalisedDirection;
	D3DXVec3Normalize(&normalisedDirection, &direction);
	velocity_ = normalisedDirection * BULLET_SPEED;
}

void Bullet::Update(System *system)
{
	D3DXVECTOR3 position = GetPosition();
	D3DXVec3Add(&position, &position, &velocity_);
	SetPosition(position);

	lifeTime -= 0.07;
}

void Bullet::Render(Graphics *graphics) const
{
	const float RADIUS = 3.0f;

	struct DummyVert
	{
		float x, y, z;
		D3DCOLOR diffuse;
	};

	DummyVert square[5] =
	{
		{-RADIUS, -RADIUS, 0.0f, 0xff00ffff},
		{-RADIUS,  RADIUS, 0.0f, 0xff00ffff },
		{ RADIUS,  RADIUS, 0.0f, 0xff00ffff },
		{ RADIUS, -RADIUS, 0.0f, 0xff00ffff },
		{-RADIUS, -RADIUS, 0.0f, 0xff00ffff },
	};

	D3DXVECTOR3 position = GetPosition();
	D3DXMATRIX translationMatrix;
	D3DXMatrixTranslation(&translationMatrix,
		position.x,
		position.y,
		position.z);

	D3DXMATRIX identityMatrix;
	D3DXMatrixIdentity(&identityMatrix);

	DWORD dummyFvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	graphics->SetVertexFormat(dummyFvf);
	graphics->DisableLighting();
	graphics->SetModelMatrix(&translationMatrix);
	graphics->DrawImmediate(D3DPT_LINESTRIP,
		4,
		&square[0],
		sizeof(square[0]));
	graphics->SetModelMatrix(&identityMatrix);
	graphics->EnableLighting();
}
