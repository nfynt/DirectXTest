#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

#include "GameEntity.h"

class Graphics;

class Ship : public GameEntity
{
public:
	Ship();

	void SetControlInput(float acceleration,
		float rotation);

	void Update(System *system);
	void Render(Graphics *graphics) const;

	D3DXVECTOR3 GetForwardVector() const;
	D3DXVECTOR3 GetVelocity() const;

	void Reset();

private:

	float accelerationControl_;
	float rotationControl_;

	D3DXVECTOR3 velocity_;
	D3DXVECTOR3 forward_;
	float rotation_;

};

#endif // SHIP_H_INCLUDED
