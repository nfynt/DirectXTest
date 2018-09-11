#ifndef ORTHOCAMERA_H_INCLUDED
#define ORTHOCAMERA_H_INCLUDED

#include <d3dx9math.h>

class Graphics;

class OrthoCamera
{
public:
	OrthoCamera();

	void SetPosition(const D3DXVECTOR3 &position);
	void SetFrustum(float width,
		float height,
		float nearZ,
		float farZ);

	void SetAsView(Graphics *graphics) const;

private:

	D3DXVECTOR3 position_;
	D3DXVECTOR2 widthHeight_;
	D3DXVECTOR2 nearFarZ_;

};

#endif // ORTHOCAMERA_H_INCLUDED
