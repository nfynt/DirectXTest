#include "Font.h"

Font::Font(ID3DXFont *font) :
	font_(font)
{
}

Font::~Font()
{
}

Font *Font::CreateXFont(const std::string &fontName,
	int height,
	IDirect3DDevice9 *d3ddevice)
{
	ID3DXFont *dxFont = 0;
	HRESULT hr = D3DXCreateFont(d3ddevice,
		height,
		0,
		FW_NORMAL,
		0,
		FALSE,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		fontName.c_str(),
		&dxFont);
	return (SUCCEEDED(hr) ? new Font(dxFont) : 0);
}

void Font::DestroyXFont(Font *font)
{
	font->font_->Release();
	delete font;
}

int Font::DrawText(const std::string &text,
	int x,
	int y,
	D3DCOLOR colour)
{
	RECT pos;
	pos.left = x;
	pos.top = y;
	pos.right = x;
	pos.bottom = y;

	int outHeight = font_->DrawText(0,
		text.c_str(),
		-1,
		&pos,
		DT_LEFT | DT_NOCLIP,
		colour);

	return outHeight;
}

int Font::CalculateTextWidth(const std::string &text)
{
	RECT pos;
	pos.left = 0;
	pos.top = 0;
	pos.right = 0;
	pos.bottom = 0;

	int outHeight = font_->DrawText(0,
		text.c_str(),
		-1,
		&pos,
		DT_CALCRECT | DT_LEFT | DT_NOCLIP | DT_SINGLELINE,
		0);

	return pos.right;
}
