#pragma once
#include "..\BasicInclude.h"

namespace TextRenderer{

	extern unsigned int asciiFontTex;
	extern unsigned int asciiFontListBase;
	extern unsigned int unicodeFontTex[256];
	extern bool unicodeFontTexAval[256];
	extern float fontColor[4];
	extern bool useUnicodeAsciiFont;

	void buildAsciiFont();
	void setFontColor(float r, float g, float b, float a);
	void PrintAscii(int x, int y, string s,bool shadowed);
	void PrintUnicode(int x, int y, string s);

}