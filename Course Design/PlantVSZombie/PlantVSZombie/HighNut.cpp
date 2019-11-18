//
// Created by rinko on 2019/11/15.
//

#include "HighNut.h"

HighNut::HighNut(int attackPower, const Point& point, Color color, int remainBlood)
	: Plant(attackPower, point, color, remainBlood) {
}


void HighNut::start() {
}

void HighNut::draw() {
	setTextColor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getCoord());
	cout << "¸ß¼á¹û";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getNextLineCoord());
	cout << (int)(remainBlood / 4) << "% ";
	resetTextColor();
}
