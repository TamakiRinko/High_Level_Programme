//
// Created by rinko on 2019/11/11.
//

#include "Nut.h"

Nut::Nut(int attackPower, const Point& point, Color color, int remainBlood)
	: Plant(attackPower, point, color, remainBlood) {
}


void Nut::start() {
}

void Nut::draw() {
	setTextColor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getCoord());
	cout << "¼á¹û";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getNextLineCoord());
	cout << (int)(remainBlood / 2.5) << "% ";
	resetTextColor();
}


