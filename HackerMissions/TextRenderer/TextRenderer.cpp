#include "TextRenderer.h"

/*
	字体渲染，其中有两种渲染方式，分别是Unicode字体和ASCII字体。
	ASCII字体在初始时加载纹理并为每个字符建立显示列表，渲染时
	调用显示列表；Unicode字体分256张纹理，每张纹理256个字符，在
	渲染时加载纹理（若已加载过则不用加载）并直接画上去。
	ASCII字符渲染效率比Unicode字符渲染效率简直快了几百倍QAQ
												——qiaozhanrong
*/

namespace TextRenderer{

	unsigned int asciiFontTex;        //ASCII字体纹理
	unsigned int asciiFontListBase;   //ASCII字体的第一个显示列表
	unsigned int unicodeFontTex[256]; //Unicode字体纹理
	bool unicodeFontTexAval[256];     //Unicode纹理是否加载
	float fontColor[4];               //字体颜色
	bool useUnicodeAsciiFont;         //强制使用Unicode字体

	void buildAsciiFont(){
		//建立ASCII字体显示列表
		float cx, cy;
		asciiFontTex = Textures::CreateTextureRGBA(Textures::LoadMaskBitmap("res\\Textures\\Fonts\\ASCII.bmp"));
		glBindTexture(GL_TEXTURE_2D, asciiFontTex);
		for (int i = 0; i < 256; i++){
			cx = (float)((i % 16) / 16.0);
			cy = (float)((i / 16) / 16.0);
			glNewList(asciiFontListBase + i, GL_COMPILE); {
				glBegin(GL_QUADS); {
					glTexCoord2f(cx, 1 - cy);
					glVertex2i(0, 0);
					glTexCoord2f(cx + 0.0625f, 1 - cy);
					glVertex2i(16, 0);
					glTexCoord2f(cx + 0.0625f, 1 - cy - 0.0625f);
					glVertex2i(16, 16);
					glTexCoord2f(cx, 1 - cy - 0.0625f);
					glVertex2i(0, 16);
				}glEnd();
				glTranslatef(10, 0, 0);
			}glEndList();
		}
		return;
	}

	void setFontColor(float r, float g, float b, float a){
		//设置字体颜色
		fontColor[0] = r; fontColor[1] = g; fontColor[2] = b; fontColor[3] = a;
		return;
	}

	void PrintAscii(int x, int y, string s, bool shadowed){
		//ASCII字体渲染
		glBindTexture(GL_TEXTURE_2D, asciiFontTex);
		glPushMatrix(); {
			if(shadowed){
				//画阴影
				glLoadIdentity();
				glColor4f(0.5, 0.5, 0.5, fontColor[3]);
				glTranslatef((float)x + 1, (float)y + 1, 0);
				glListBase(asciiFontListBase);
				glCallLists(s.size(), GL_UNSIGNED_BYTE, s.c_str());
			}
			//画文字
			glLoadIdentity();
			glColor4fv(fontColor);
			glTranslatef((float)x, (float)y, 0);
			glListBase(asciiFontListBase);
			glCallLists(s.size(), GL_UNSIGNED_BYTE, s.c_str());
		}glPopMatrix();
		return;
	}

	void PrintUnicode(int x, int y, string s){
		//Unicode字体渲染
		
		return;
	}

}