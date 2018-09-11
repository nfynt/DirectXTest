#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include "AssetManager.h"
#include "Font.h"
#include <d3d9.h>
#include <d3dx9math.h>
#include <string>
#include <map>

class Graphics
{
public:
	static Graphics *CreateDevice(HWND window);
	static void DestroyDevice(Graphics *device);

	void BeginFrame();
	void EndFrame();

	Font *CreateXFont(const std::string &fontName, int height) const;
	void DestroyXFont(Font *font) const;

	void ClearFrame(D3DCOLOR colour);
	void SetModelMatrix(const D3DXMATRIX *modelMatrix);
	void SetViewMatrix(const D3DXMATRIX *viewMatrix);
	void SetProjectionMatrix(const D3DXMATRIX *projectionMatrix);

	void SetVertexFormat(DWORD fvf);
	void DrawImmediate(D3DPRIMITIVETYPE primType,
		unsigned int primCount,
		const void *vertexBuffer,
		unsigned int vertexStride);

	void SetPointSize(float size);

	void DisableLighting();
	void EnableLighting();

private:
	Graphics(IDirect3D9 *d3d, IDirect3DDevice9 *d3dDevice);
	~Graphics();

	Graphics(const Graphics &);
	void operator=(const Graphics &);

	IDirect3D9 *d3d_;
	IDirect3DDevice9 *d3dDevice_;
	D3DVIEWPORT9 defaultViewport_;

	D3DXMATRIX modelMatrix_;
	D3DXMATRIX viewMatrix_;
	D3DXMATRIX projectionMatrix_;
};

#endif GRAPHICS_H_INCLUDED
