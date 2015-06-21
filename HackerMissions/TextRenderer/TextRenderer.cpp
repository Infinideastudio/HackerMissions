#include "TextRenderer.h"

/*
	������Ⱦ��������������Ⱦ��ʽ���ֱ���Unicode�����ASCII���塣
	ASCII�����ڳ�ʼʱ��������Ϊÿ���ַ�������ʾ�б���Ⱦʱ
	������ʾ�б�Unicode�����256������ÿ������256���ַ�����
	��Ⱦʱ�����������Ѽ��ع����ü��أ���ֱ�ӻ���ȥ��
	ASCII�ַ���ȾЧ�ʱ�Unicode�ַ���ȾЧ�ʼ�ֱ���˼��ٱ�QAQ
												����qiaozhanrong
*/

namespace TextRenderer{

	unsigned int asciiFontTex;        //ASCII��������
	unsigned int asciiFontListBase;   //ASCII����ĵ�һ����ʾ�б�
	unsigned int unicodeFontTex[256]; //Unicode��������
	bool unicodeFontTexAval[256];     //Unicode�����Ƿ����
	float fontColor[4];               //������ɫ
	bool useUnicodeAsciiFont;         //ǿ��ʹ��Unicode����

	void buildAsciiFont(){
		//����ASCII������ʾ�б�
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
		//����������ɫ
		fontColor[0] = r; fontColor[1] = g; fontColor[2] = b; fontColor[3] = a;
		return;
	}

	void PrintAscii(int x, int y, string s, bool shadowed){
		//ASCII������Ⱦ
		glBindTexture(GL_TEXTURE_2D, asciiFontTex);
		glPushMatrix(); {
			if(shadowed){
				//����Ӱ
				glLoadIdentity();
				glColor4f(0.5, 0.5, 0.5, fontColor[3]);
				glTranslatef((float)x + 1, (float)y + 1, 0);
				glListBase(asciiFontListBase);
				glCallLists(s.size(), GL_UNSIGNED_BYTE, s.c_str());
			}
			//������
			glLoadIdentity();
			glColor4fv(fontColor);
			glTranslatef((float)x, (float)y, 0);
			glListBase(asciiFontListBase);
			glCallLists(s.size(), GL_UNSIGNED_BYTE, s.c_str());
		}glPopMatrix();
		return;
	}

	void PrintUnicode(int x, int y, string s){
		//Unicode������Ⱦ
		
		return;
	}

}