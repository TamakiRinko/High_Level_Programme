//
// Created by rinko on 2019/11/14.
//

#include "Garlic.h"


Garlic::Garlic(int attackPower, const Point& point, Color color, int remainBlood)
	: Plant(attackPower, point, color, remainBlood) {
}

void Garlic::start(){
	
}

void Garlic::draw(){
	setTextColor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getCoord());
	cout << "´óËâ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), getNextLineCoord());
	cout << (int)(remainBlood * 2) << "% ";
	resetTextColor();
}
