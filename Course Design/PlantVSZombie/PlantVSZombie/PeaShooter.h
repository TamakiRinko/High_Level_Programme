//
// Created by rinko on 2019/11/11.
//

#ifndef PLANTSVSZOMBIES_PEASHOOTER_H
#define PLANTSVSZOMBIES_PEASHOOTER_H

#include "Plant.h"

class PeaShooter : public Plant {
public:
	PeaShooter(int attackPower, const Point& point, Color color, int remainBlood);
	void start() override;

	void draw() override;
};


#endif //PLANTSVSZOMBIES_PEASHOOTER_H
