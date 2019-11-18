//
// Created by rinko on 2019/11/11.
//

#ifndef PLANTSVSZOMBIES_NORMALZOMBIE_H
#define PLANTSVSZOMBIES_NORMALZOMBIE_H

#include "Zombie.h"

class NormalZombie : public Zombie {
public:
	NormalZombie(int speed, int attackPower, const Point &point, Color color, int score, int remainBlood);

	void draw() override;
};


#endif //PLANTSVSZOMBIES_NORMALZOMBIE_H
