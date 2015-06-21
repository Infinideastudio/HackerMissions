#include "Level.h"
#include "..\BasicInclude.h"

bool level::readFromFile(int levelload){
	if (isMapLoaded){ //�Ѿ����ع���ͼ�ˣ�ɾ����ǰ��ͼ
		delete[] mapData;
	}
	std::stringstream ss;
	ss << "res\\levels\\level" << levelload << ".dat"; //�ؿ��ļ���
	std::ifstream levelfile(ss.str(),std::ios::binary|std::ios::in); //���ļ�
	int levelID = 0;
	levelfile.read((char*)&levelID,sizeof(int)); //����ؿ���
	if (levelID != levelload) return false; //��֤�ؿ���
	levelfile.read((char*)&mapx, sizeof(int)); //�����ͼ��СX
	levelfile.read((char*)&mapy, sizeof(int)); //�����ͼ��СY
	mapData = new unsigned char[mapx*mapy]; //�����ͼ����
	isMapLoaded = true;
	levelfile.read((char*)mapData,sizeof(unsigned char)*mapx*mapy);
	levelfile.close();
	LevelID = levelload;
	return true;
}
