//
// Created by rinko on 2019/11/11.
//

#include "PeaShooter.h"
extern unordered_set<Bullet* > bulletList;										//���ڵ��ӵ��б�

PeaShooter::PeaShooter(int attackPower, const Point& point, Color color, int remainBlood)
	: Plant(attackPower, point, color, remainBlood) {
}

void PeaShooter::start(){
	interval++;
	if (interval >= 70){
		interval = 0;
		Point* bulletPoint = new Point(this->point.x * 9 + 4, this->point.y * 16 + 12);
		Bullet* bullet = new Bullet(8, attackPower, *bulletPoint, RED, 100);
		bulletList.insert(bullet);
	}
}

void PeaShooter::draw(){
	setTextColor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getCoord());
	cout << "�㶹����";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getNextLineCoord());
	cout << remainBlood << "% ";
	resetTextColor();
}
