#include "Asteroid.h"
#include "Graphics.h"
#include "Random.h"
#include "Maths.h"

Asteroid::Asteroid(const D3DXVECTOR3 &position,
	const D3DXVECTOR3 &velocity,
	int size) :
	velocity_(velocity),
	angle_(0.0f),
	size_(size)
{
	SetPosition(position);
	axis_.x = Random::GetFloat(-1.0f, 1.0f);
	axis_.y = Random::GetFloat(-1.0f, 1.0f);
	axis_.z = Random::GetFloat(-1.0f, 1.0f);
	D3DXVec3Normalize(&axis_, &axis_);

	const float MAX_ROTATION = 0.3f;
	angularSpeed_ = Random::GetFloat(-MAX_ROTATION, MAX_ROTATION);
}

void Asteroid::Update(System *system)
{
	D3DXVECTOR3 position = GetPosition();
	D3DXVec3Add(&position, &position, &velocity_);
	SetPosition(position);

	angle_ = Maths::WrapModulo(angle_ + angularSpeed_, Maths::TWO_PI);
}

void Asteroid::Render(Graphics *graphics) const
{
	const float RADIUS_MULTIPLIER = 5.0f;

	struct DummyVert
	{
		float x, y, z;
		D3DCOLOR diffuse;
	};

	DummyVert square[5] =
	{
		{-1.0f, -1.0f, 0.0f, 0xffffffff},
		{-1.0f,  1.0f, 0.0f, 0xffffffff},
		{ 1.0f,  1.0f, 0.0f, 0xffffffff},
		{ 1.0f, -1.0f, 0.0f, 0xffffffff},
		{-1.0f, -1.0f, 0.0f, 0xffffffff},
	};

	D3DXMATRIX scaleMatrix;
	D3DXMatrixScaling(&scaleMatrix,
		size_ * RADIUS_MULTIPLIER,
		size_ * RADIUS_MULTIPLIER,
		size_ * RADIUS_MULTIPLIER);

	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationAxis(&rotationMatrix, &axis_, angle_);

	D3DXVECTOR3 position = GetPosition();
	D3DXMATRIX translationMatrix;
	D3DXMatrixTranslation(&translationMatrix,
		position.x,
		position.y,
		position.z);

	D3DXMATRIX asteroidTransform = scaleMatrix *
		rotationMatrix *
		translationMatrix;

	D3DXMATRIX identityMatrix;
	D3DXMatrixIdentity(&identityMatrix);

	DWORD dummyFvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	graphics->SetVertexFormat(dummyFvf);
	graphics->DisableLighting();
	graphics->SetModelMatrix(&asteroidTransform);
	graphics->DrawImmediate(D3DPT_LINESTRIP,
		4,
		&square[0],
		sizeof(square[0]));
	graphics->SetModelMatrix(&identityMatrix);
	graphics->EnableLighting();

}

D3DXVECTOR3 Asteroid::GetVelocity() const
{
	return velocity_;
}

int Asteroid::GetSize() const
{
	return size_;
}
