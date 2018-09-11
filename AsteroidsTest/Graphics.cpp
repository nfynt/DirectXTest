#include "Graphics.h"
#include "Font.h"

Graphics::Graphics(IDirect3D9 *d3d, IDirect3DDevice9 *d3dDevice) :
	d3d_(d3d),
	d3dDevice_(d3dDevice)
{
	defaultViewport_.X = 0;
	defaultViewport_.Y = 0;
	defaultViewport_.Width = 800;
	defaultViewport_.Height = 600;
	defaultViewport_.MinZ = 0.0f;
	defaultViewport_.MaxZ = 1.0f;

	D3DXMatrixIdentity(&modelMatrix_);
	D3DXMatrixIdentity(&viewMatrix_);
	D3DXMatrixIdentity(&projectionMatrix_);
}

Graphics::~Graphics()
{
}

Graphics *Graphics::CreateDevice(HWND window)
{
	IDirect3D9 *d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == 0)
	{
		return 0;
	}

	D3DPRESENT_PARAMETERS pp;
	ZeroMemory(&pp, sizeof(pp));
	pp.BackBufferWidth = 800;
	pp.BackBufferHeight = 600;
	pp.BackBufferFormat = D3DFMT_A8R8G8B8;
	pp.BackBufferCount = 2;
	pp.MultiSampleType = D3DMULTISAMPLE_NONE;
	pp.MultiSampleQuality = 0;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.hDeviceWindow = window;
	pp.Windowed = true;
	pp.EnableAutoDepthStencil = true;
	pp.AutoDepthStencilFormat = D3DFMT_D24S8;
	pp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	pp.FullScreen_RefreshRateInHz = 0;
	pp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	IDirect3DDevice9 *device = 0;
	HRESULT hr = d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&pp,
		&device);
	if (FAILED(hr))
	{
		return 0;
	}

	return new Graphics(d3d, device);
}

void Graphics::DestroyDevice(Graphics *device)
{
	device->d3dDevice_->Release();
	device->d3d_->Release();
	delete device;
}

void Graphics::BeginFrame()
{
	d3dDevice_->BeginScene();

	static unsigned int clearColour = 0;
	clearColour += 5;
	ClearFrame(clearColour);

	d3dDevice_->SetViewport(&defaultViewport_);
}

void Graphics::EndFrame()
{
	d3dDevice_->EndScene();
	d3dDevice_->Present(0, 0, 0, 0);
}

Font *Graphics::CreateXFont(const std::string &fontName, int height) const
{
	return Font::CreateXFont(fontName, height, d3dDevice_);
}

void Graphics::DestroyXFont(Font *font) const
{
	Font::DestroyXFont(font);
}

void Graphics::ClearFrame(D3DCOLOR colour)
{
	d3dDevice_->Clear(0,
		0,
		D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		colour,
		1.0f,
		0);
}

void Graphics::SetModelMatrix(const D3DXMATRIX *modelMatrix)
{
	modelMatrix_ = *modelMatrix;
	d3dDevice_->SetTransform(D3DTS_WORLD, &modelMatrix_);
}

void Graphics::SetViewMatrix(const D3DXMATRIX *viewMatrix)
{
	viewMatrix_ = *viewMatrix;
	d3dDevice_->SetTransform(D3DTS_VIEW, &viewMatrix_);
}

void Graphics::SetProjectionMatrix(const D3DXMATRIX *projectionMatrix)
{
	projectionMatrix_ = *projectionMatrix;
	d3dDevice_->SetTransform(D3DTS_PROJECTION, &projectionMatrix_);
}

void Graphics::SetVertexFormat(DWORD fvf)
{
	d3dDevice_->SetFVF(fvf);
}

void Graphics::DrawImmediate(D3DPRIMITIVETYPE primType,
	unsigned int primCount,
	const void *vertexBuffer,
	unsigned int vertexStride)
{
	d3dDevice_->DrawPrimitiveUP(primType,
		primCount,
		vertexBuffer,
		vertexStride);
}

void Graphics::SetPointSize(float size)
{
	d3dDevice_->SetRenderState(D3DRS_POINTSIZE, reinterpret_cast<DWORD &>(size));
}

void Graphics::DisableLighting()
{
	d3dDevice_->SetRenderState(D3DRS_LIGHTING, FALSE);
}

void Graphics::EnableLighting()
{
	d3dDevice_->SetRenderState(D3DRS_LIGHTING, TRUE);
}
