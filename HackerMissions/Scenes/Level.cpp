#include "Level.h"
#include "..\BasicInclude.h"

bool level::readFromFile(int levelload){
	if (isMapLoaded){ //已经加载过地图了，删除当前地图
		delete[] mapData;
	}
	std::stringstream ss;
	ss << "res\\levels\\level" << levelload << ".dat"; //关卡文件名
	std::ifstream levelfile(ss.str(),std::ios::binary|std::ios::in); //打开文件
	int levelID = 0;
	levelfile.read((char*)&levelID,sizeof(int)); //读入关卡号
	if (levelID != levelload) return false; //验证关卡号
	levelfile.read((char*)&mapx, sizeof(int)); //读入地图大小X
	levelfile.read((char*)&mapy, sizeof(int)); //读入地图大小Y
	mapData = new unsigned char[mapx*mapy]; //分配地图数据
	isMapLoaded = true;
	levelfile.read((char*)mapData,sizeof(unsigned char)*mapx*mapy);
	levelfile.close();
	LevelID = levelload;
	return true;
}
