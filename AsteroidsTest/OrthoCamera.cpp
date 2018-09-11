#include "OrthoCamera.h"
#include "Graphics.h"

OrthoCamera::OrthoCamera() :
	position_(0.0f, 0.0f, 0.0f),
	widthHeight_(1.0f, 1.0f),
	nearFarZ_(0.0, 1.0f)
{
}

void OrthoCamera::SetPosition(const D3DXVECTOR3 &position)
{
	position_ = position;
}

void OrthoCamera::SetFrustum(float width,
	float height,
	float nearZ,
	float farZ)
{
	widthHeight_ = D3DXVECTOR2(width, height);
	nearFarZ_ = D3DXVECTOR2(nearZ, farZ);
}

void OrthoCamera::SetAsView(Graphics *graphics) const
{
	D3DXMATRIX ortho;
	D3DXMatrixOrthoLH(&ortho,
		widthHeight_.x,
		widthHeight_.y,
		nearFarZ_.x,
		nearFarZ_.y);

	graphics->SetProjectionMatrix(&ortho);
}
