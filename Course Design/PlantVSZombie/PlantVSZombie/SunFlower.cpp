//
// Created by rinko on 2019/11/11.
//

#include "SunFlower.h"
#include "Paint.h"
extern Paint paint;														//»­±Ê

SunFlower::SunFlower(int attackPower, const Point& point, Color color, int remainBlood)
	: Plant(attackPower, point, color, remainBlood) {
}


void SunFlower::start(){
	interval++;
	if (interval >= 40){
		interval = 0;
		curSunNumMutex.lock();
		curSunNum = curSunNum + 25;
		curSunNumMutex.unlock();
		paint.paintSunNum();
	}
}

void SunFlower::draw(){
	setTextColor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getCoord());
	cout << "ÏòÈÕ¿û";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getNextLineCoord());
	cout << remainBlood << "% ";
	resetTextColor();
}


