//
// Created by rinko on 2019/11/11.
//

#include "NormalZombie.h"
#include "ZombieReflector.h"

ZOMBIEREFLECT(NormalZombie, (int)ZombieType::NORMAL)

NormalZombie::NormalZombie(ZombieType zombieType, Point* point): Zombie(zombieType, point) {}

NormalZombie::NormalZombie(int speed, int attackPower, const Point &point, Color color, int score, int remainBlood) :
	Zombie(speed, attackPower, point, color, score, remainBlood) {}


void NormalZombie::draw(){
	setTextColor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getCoord());
	cout << "½©Ê¬";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getNextLineCoord());
	cout << remainBlood << "% ";
	resetTextColor();
}
