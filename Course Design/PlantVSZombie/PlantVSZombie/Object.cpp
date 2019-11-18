//
// Created by rinko on 2019/11/11.
//

#include "Object.h"

ostream& operator<<(ostream& out, const Point& point){
	out << "(" << point.x << ", " << point.y << ")";
	return out;
}

Object::Object(int attackPower, const Point &point, Color color, int remainBlood) :
remainBlood(remainBlood), attackPower(attackPower), point(point), color(color), /*isRunning(false),*/ isModified(true), interval(0){}

void Object::setTextColor(){
	HANDLE handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(handle, &csbi);
	SetConsoleTextAttribute(handle, color);
}

void Object::resetTextColor(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
		FOREGROUND_GREEN | FOREGROUND_BLUE);
}

COORD& Object::getCoord(){
	COORD* coord = new COORD();
	coord->X = point.y * 16 + 1;
	coord->Y = point.x * 9 + 4;
	return *coord;
}

COORD& Object::getNextLineCoord(){
	COORD* coord = new COORD();
	coord->X = point.y * 16 + 1;
	coord->Y = point.x * 9 + 5;
	return *coord;
}

int Object::getRemainBlood() const {
	return remainBlood;
}

void Object::setRemainBlood(int remainBlood) {
	Object::remainBlood = remainBlood;
}

int Object::getAttackPower() const {
	return attackPower;
}

void Object::setAttackPower(int attackPower) {
	Object::attackPower = attackPower;
}

const Point &Object::getPoint() const {
	return point;
}

void Object::setPoint(const Point &point) {
	Object::point = point;
}

bool Object::getIsModified(){
	return isModified;
}

void Object::resetIsModified(){
	isModified = false;
}

Object::~Object() {

}

// void Object::stop(){
// 	isRunning = false;
// }
