//
// Created by rinko on 2019/11/14.
//

#ifndef PLANTSVSZOMBIES_NUT_H
#define PLANTSVSZOMBIES_NUT_H

#include "Plant.h"

class Nut : public Plant {
public:
	Nut(int attackPower, const Point& point, Color color, int remainBlood);

	void start() override;
	void draw() override;
};


#endif //PLANTSVSZOMBIES_NUT_H