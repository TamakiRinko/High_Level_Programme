//
// Created by rinko on 2019/11/15.
//

#ifndef PLANTSVSZOMBIES_HIGHNUT_H
#define PLANTSVSZOMBIES_HIGHNUT_H

#include "Plant.h"

class HighNut : public Plant {
public:
	HighNut(int attackPower, const Point& point, Color color, int remainBlood);

	void start() override;
	void draw() override;
};


#endif //PLANTSVSZOMBIES_HIGHNUT_H

