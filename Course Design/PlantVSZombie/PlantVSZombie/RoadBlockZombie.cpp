//
// Created by rinko on 2019/11/11.
//

#include "RoadBlockZombie.h"
#include "Paint.h"

extern Paint paint;															//»­±Ê

RoadBlockZombie::RoadBlockZombie(int speed, int attackPower, const Point &point, Color color, int score, int remainBlood, bool hasRoadBlock) :
	Zombie(speed, attackPower, point, color, score, remainBlood), hasRoadBlock(hasRoadBlock) {}


bool RoadBlockZombie::attacked(int damage){
	isModified = true;
	remainBlood = remainBlood - damage;
	if (remainBlood <= 0) {											//ËÀÍö
		remainBlood = 0;
		return true;
	} else if (remainBlood <= 100){
		hasRoadBlock = false;
	}
	return false;													//Î´ËÀÍö
}

void RoadBlockZombie::draw() {
	setTextColor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getCoord());
	cout << "Â·ÕÏ½©Ê¬";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getNextLineCoord());
	if (hasRoadBlock){
		cout << "ÓÐÃ±×Ó";
	} else{
		cout << "ÎÞÃ±×Ó";
	}
	resetTextColor();
}
