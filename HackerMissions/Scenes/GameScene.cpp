#include "GameScene.h"

void GameScene::init(){
	levelid = 0;
	levelup();
}

void GameScene::draw(){

}

void GameScene::levelup(){
	levelnow.readFromFile(levelid++);
}