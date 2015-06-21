#include "Level.h"
#include "..\BasicInclude.h"

bool level::readFromFile(int levelload){
	if (isMapLoaded){ //已经加载过地图了，删除当前地图
		delete[] mapData;
	}
	std::stringstream ss;
	ss << "levels\\level" << levelload << ".dat";
	FILE* levelfile;
	errno_t err = fopen_s(&levelfile,ss.str().c_str(), "r"); //以只读方式打开关卡文件
	if (err != 0 || levelfile == nullptr) return false;  //验证打开文件是否成功
	int levelID = 0;
	fread(&levelID, sizeof(int), 1, levelfile);
	if (levelID != levelload) return false; //验证关卡号
	fread(&mapx, sizeof(int), 1, levelfile); //读入关卡大小
	fread(&mapy, sizeof(int), 1, levelfile); //读入关卡大小
	mapData = new unsigned char[mapx*mapy]; //分配地图数据
	isMapLoaded = true;
	memset(mapData, 0, sizeof(mapData));
	fread(mapData, sizeof(mapData), 1, levelfile); //读入地图数据
	fclose(levelfile);
	LevelID = levelload;
	return true;
}
