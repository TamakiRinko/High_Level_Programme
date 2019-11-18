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
	KeyBoardMode keyBoardMode;						//��ǰ��������ģʽ
	
	Point* curShopPos;								//�̵���ѡ���λ��
	Point* curMapPos;								//��ͼ��ѡ���λ��
	Plant* curPlant;								//��ǰѡ���ֲ��
	PlantType curPlantType;							//��ǰ��Ҫ��ֲ��ֲ�������
	int curPlantCost;								//��ǰֲ������������

	void keyBoardAction();
	void mainLogic();
	
	void generateZombie();							//�������һ����ʬ
	void generatePlant();							//ָ��λ����ֲһ��ֲ��
	void buyPlant();								//���̵��ﹺ��ֲ��
	void shovelPlant();
	bool modeCapture(char key);						//ģʽ����ѡ��
	void keyCapture(char key);						//���ఴ��ѡ��

	void generateNaturalSun();						//ÿ���������25��Ȼ��
	

public:
	Control();
	void start();
};


#endif //PLANTSVSZOMBIES_CONTROL_H
