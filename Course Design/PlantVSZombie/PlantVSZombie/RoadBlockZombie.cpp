//
// Created by rinko on 2019/11/11.
//

#include "RoadBlockZombie.h"
#include "Paint.h"
#include "ZombieReflector.h"

extern Paint paint;															//����

ZOMBIEREFLECT(RoadBlockZombie, (int)ZombieType::ROADBLOCK)

RoadBlockZombie::RoadBlockZombie(int speed, int attackPower, const Point &point, Color color, int score, int remainBlood, bool hasRoadBlock) :
	Zombie(speed, attackPower, point, color, score, remainBlood), hasRoadBlock(hasRoadBlock) {}

RoadBlockZombie::RoadBlockZombie(ZombieType zombieType, Point* point): Zombie(zombieType, point), hasRoadBlock(true){}


bool RoadBlockZombie::attacked(int damage){
	isModified = true;
	remainBlood = remainBlood - damage;
	if (remainBlood <= 0) {											//����
		remainBlood = 0;
		return true;
	} else if (remainBlood <= 100){
		hasRoadBlock = false;
	}
	return false;													//δ����
}

void RoadBlockZombie::draw() {
	setTextColor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getCoord());
	cout << "·�Ͻ�ʬ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getNextLineCoord());
	if (hasRoadBlock){
		cout << "��ñ��";
	} else{
		cout << "��ñ��";
	}
	resetTextColor();
}