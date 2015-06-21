#include "Level.h"
#include "..\BasicInclude.h"

bool level::readFromFile(int levelload){
	if (isMapLoaded){ //�Ѿ����ع���ͼ�ˣ�ɾ����ǰ��ͼ
		delete[] mapData;
	}
	std::stringstream ss;
	ss << "levels\\level" << LevelID << ".dat";
	FILE* levelfile;
	fopen_s(&levelfile,ss.str().c_str(), "r"); //��ֻ����ʽ�򿪹ؿ��ļ�
	if (levelfile == NULL) return false;  //��֤���ļ��Ƿ�ɹ�
	int levelID = 0;
	fread(&levelID, sizeof(int), 1, levelfile);
	if (levelID != levelload) return false; //��֤�ؿ���
	fread(&mapx, sizeof(int), 1, levelfile); //����ؿ���С
	fread(&mapy, sizeof(int), 1, levelfile); //����ؿ���С
	mapData = new unsigned char[mapx*mapy]; //�����ͼ����
	isMapLoaded = true;
	fread(&mapData, sizeof(mapData), 1, levelfile); //�����ͼ����
	fclose(levelfile);
	LevelID = levelload;
	return true;
}