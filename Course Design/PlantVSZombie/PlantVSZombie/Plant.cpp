//
// Created by rinko on 2019/11/11.
//

#include "Plant.h"
#include "Paint.h"

// extern Paint paint;														//»­±Ê

Plant::Plant(int attackPower, const Point &point, Color color, int remainBlood) :
	Object(attackPower, point, color, remainBlood) {}

bool Plant::attacked(int damage){
	isModified = true;
	remainBlood = remainBlood - damage;
	if (remainBlood <= 0){											//ËÀÍö
		remainBlood = 0;
		return true;
	}
	return false;													//Î´ËÀÍö
}
