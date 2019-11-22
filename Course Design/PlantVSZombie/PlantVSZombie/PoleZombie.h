//
// Created by rinko on 2019/11/15.
//

#ifndef PLANTSVSZOMBIES_POLEZOMBIE_H
#define PLANTSVSZOMBIES_POLEZOMBIE_H

#include "Zombie.h"

class PoleZombie : public Zombie {
private:
	bool hasPole;
public:
	PoleZombie(int speed, int attackPower, const Point &point, Color color, int score, int remainBlood);
	PoleZombie(ZombieType zombieType, Point* point);
	bool jump();
	void start() override;
	void draw() override;
};


#endif //PLANTSVSZOMBIES_POLEZOMBIE_H