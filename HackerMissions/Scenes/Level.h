#pragma once

class level{
private:
	bool isMapLoaded = false;
public:
	~level(){
		if(isMapLoaded) delete[] mapData;
	}
	int LevelID = 0;
	int mapx;
	int mapy;
	unsigned char* mapData;
	bool readFromFile(int levelload); //����true������سɹ���false�������ʧ��
};