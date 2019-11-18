//
// Created by rinko on 2019/11/14.
//

#ifndef PLANTSVSZOMBIES_GARLIC_H
#define PLANTSVSZOMBIES_GARLIC_H

#include "Plant.h"


class Garlic: public Plant {
public:
	Garlic(int attackPower, const Point& point, Color color, int remainBlood);
	void start() override;

	void draw() override;
};

#endif
