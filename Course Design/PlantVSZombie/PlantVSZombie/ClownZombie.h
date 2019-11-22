//
// Created by rinko on 2019/11/14.
//

#ifndef PLANTSVSZOMBIES_CLOWNZOMBIE_H
#define PLANTSVSZOMBIES_CLOWNZOMBIE_H

#include "Zombie.h"
#include <random>

class ClownZombie : public Zombie {
private:
	bool explosion();
public:
	ClownZombie(int speed, int attackPower, const Point &point, Color color, int score, int remainBlood);
	ClownZombie(ZombieType zombieType, Point* point);
	void start() override;
	void draw() override;
};


#endif //PLANTSVSZOMBIES_CLOWMZOMBIE_H


