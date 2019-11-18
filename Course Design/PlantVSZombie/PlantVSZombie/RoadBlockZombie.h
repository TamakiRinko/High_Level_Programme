//
// Created by rinko on 2019/11/11.
//

#ifndef PLANTSVSZOMBIES_ROADBLOCKZOMBIE_H
#define PLANTSVSZOMBIES_ROADBLOCKZOMBIE_H

#include "Zombie.h"

class RoadBlockZombie : public Zombie {
private:
	bool hasRoadBlock;
public:
	RoadBlockZombie(int speed, int attackPower, const Point &point, Color color, int score, int remainBlood = 200, bool hasRoadBlock = true);
	void draw() override;
	bool attacked(int damage) override;
};


#endif //PLANTSVSZOMBIES_ROADBLOCKZOMBIE_H
