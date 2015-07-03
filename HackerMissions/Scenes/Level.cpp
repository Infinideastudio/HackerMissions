#include "Level.h"
#include "..\BasicInclude.h"

bool level::readFromFile(int levelload){
	if (isMapLoaded){
		delete[] mapData; //�Ѿ����ع���ͼ�ˣ�ɾ����ǰ��ͼ
		isMapLoaded = false;
	}
	std::stringstream ss;
	ss << "res\\levels\\level" << levelload << ".dat"; //�ؿ��ļ���
	std::ifstream levelfile(ss.str(),std::ios::binary|std::ios::in); //���ļ�
	if (!levelfile.is_open()) return false;
	int levelID = 0;
	levelfile.read((char*)&levelID,sizeof(int)); //����ؿ���
	if (levelID != levelload) return false; //��֤�ؿ���
	levelfile.read((char*)&mapx, sizeof(int)); //�����ͼ��СX
	levelfile.read((char*)&mapy, sizeof(int)); //�����ͼ��СY
	mapData = new unsigned char[mapx*mapy]; //�����ͼ����
	isMapLoaded = true;
	memset(mapData, 0, sizeof(mapData));
	levelfile.read((char*)mapData, sizeof(unsigned char)*mapx*mapy);
	levelfile.close();
	LevelID = levelload;
	return true;
}
