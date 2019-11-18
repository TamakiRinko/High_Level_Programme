//
// Created by rinko on 2019/11/11.
//

#include "MoveObject.h"

MoveObject::MoveObject(int speed, int attackPower, const Point &point, Color color, int remainBlood) :
	Object(attackPower, point, color, remainBlood), speed(speed) {}
