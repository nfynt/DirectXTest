#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include "GameEntity.h"

class Asteroid : public GameEntity
{
public:
	Asteroid(const D3DXVECTOR3 &position,
		const D3DXVECTOR3 &velocity,
		int size);

	void Update(System *system);
	void Render(Graphics *graphics) const;

	D3DXVECTOR3 GetVelocity() const;
	int GetSize() const;

private:

	D3DXVECTOR3 velocity_;
	D3DXVECTOR3 axis_;
	float angle_;
	float angularSpeed_;
	int size_;

};

#endif // ASTEROID_H_INCLUDED
