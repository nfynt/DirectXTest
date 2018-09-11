#ifndef FONT_H_INCLUDED
#define FONT_H_INCLUDED

#include <d3dx9core.h>
#include <string>

class Font
{
public:
	static Font *CreateXFont(const std::string &fontName,
		int height,
		IDirect3DDevice9 *d3ddevice);
	static void DestroyXFont(Font *font);

	int DrawText(const std::string &text,
		int x,
		int y,
		D3DCOLOR colour);
	int CalculateTextWidth(const std::string &text);

private:
	Font(ID3DXFont *font);
	~Font();

	Font(const Font &);
	void operator=(const Font &);

	ID3DXFont *font_;

};

#endif // FONT_H_INCLUDED
