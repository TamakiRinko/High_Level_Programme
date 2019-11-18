//
// Created by rinko on 2019/11/11.
//

#ifndef PLANTSVSZOMBIES_CONTROL_H
#define PLANTSVSZOMBIES_CONTROL_H

#include "Object.h"
#include "MoveObject.h"
#include "Zombie.h"
#include "NormalZombie.h"
#include "RoadBlockZombie.h"
#include "ClownZombie.h"
#include "PoleZombie.h"
#include "Plant.h"
#include "SunFlower.h"
#include "PeaShooter.h"
#include "Nut.h"
#include "Garlic.h"
#include "IcePeaShooter.h"
#include "HighNut.h"
#include "Shop.h"
#include "Paint.h"

#include <random>

enum KeyBoardMode{
	NORMALMODE, SHOPMODE, MAPMODE, SHOVELMODE
};

class Control {
private:
	KeyBoardMode keyBoardMode;						//当前键盘所在模式
	
	Point* curShopPos;								//商店里选择的位置
	Point* curMapPos;								//地图上选择的位置
	Plant* curPlant;								//当前选择的植物
	PlantType curPlantType;							//当前需要种植的植物的类型
	int curPlantCost;								//当前植物所需阳光数

	void keyBoardAction();
	void mainLogic();
	
	void generateZombie();							//随机生成一个僵尸
	void generatePlant();							//指定位置种植一个植物
	void buyPlant();								//从商店里购买植物
	void shovelPlant();
	bool modeCapture(char key);						//模式按键选择
	void keyCapture(char key);						//其余按键选择

	void generateNaturalSun();						//每隔五秒产生25自然光
	

public:
	Control();
	void start();
};


#endif //PLANTSVSZOMBIES_CONTROL_H
